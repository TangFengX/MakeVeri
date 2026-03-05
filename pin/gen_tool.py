import re
import sys
import os
import argparse

class NXDCConverter:
    def __init__(self, pins_db_path, verbose=False):
        self.verbose = verbose
        self.ensure_pins_db(pins_db_path)
        self.valid_pins = self.load_pins(pins_db_path)
        self.summary = []      # 存储格式: {"port": str, "width": int, "count": int}
        self.used_pins = {}    # 物理引脚 -> 端口名
        self.defined_ports = set() # 记录已定义的逻辑端口

    def log(self, msg):
        if self.verbose:
            print(f"\033[90m[DEBUG] {msg}\033[0m")

    def ensure_pins_db(self, path):
        if not os.path.exists(path):
            pins_data = "BTNC BTNU BTND BTNL BTNR SW0 SW1 SW2 SW3 SW4 SW5 SW6 SW7 SW8 SW9 SW10 SW11 SW12 SW13 SW14 SW15 LD0 LD1 LD2 LD3 LD4 LD5 LD6 LD7 LD8 LD9 LD10 LD11 LD12 LD13 LD14 LD15 R16 G16 B16 R17 G17 B17 SEG0A SEG0B SEG0C SEG0D SEG0E SEG0F SEG0G DEC0P SEG1A SEG1B SEG1C SEG1D SEG1E SEG1F SEG1G DEC1P SEG2A SEG2B SEG2C SEG2D SEG2E SEG2F SEG2G DEC2P SEG3A SEG3B SEG3C SEG3D SEG3E SEG3F SEG3G DEC3P SEG4A SEG4B SEG4C SEG4D SEG4E SEG4F SEG4G DEC4P SEG5A SEG5B SEG5C SEG5D SEG5E SEG5F SEG5G DEC5P SEG6A SEG6B SEG6C SEG6D SEG6E SEG6F SEG6G DEC6P SEG7A SEG7B SEG7C SEG7D SEG7E SEG7F SEG7G DEC7P VGA_VSYNC VGA_HSYNC VGA_BLANK_N VGA_R0 VGA_R1 VGA_R2 VGA_R3 VGA_R4 VGA_R5 VGA_R6 VGA_R7 VGA_G0 VGA_G1 VGA_G2 VGA_G3 VGA_G4 VGA_G5 VGA_G6 VGA_G7 VGA_B0 VGA_B1 VGA_B2 VGA_B3 VGA_B4 VGA_B5 VGA_B6 VGA_B7 UART_TX UART_RX PS2_CLK PS2_DAT"
            os.makedirs(os.path.dirname(path), exist_ok=True)
            with open(path, 'w') as f: f.write(pins_data)

    def load_pins(self, path):
        with open(path, 'r') as f: return set(f.read().split())

    def expand_ranges_in_brackets(self, text):
        def repl_bracket(m):
            content = m.group(1)
            def repl_range(rm):
                start, end = rm.group(1), rm.group(2)
                if start.isdigit() and end.isdigit():
                    s, e = int(start), int(end)
                    step = -1 if s > e else 1
                    return " ".join([str(i) for i in range(s, e + step, step)])
                else:
                    s, e = ord(start), ord(end)
                    step = -1 if s > e else 1
                    return " ".join([chr(i) for i in range(s, e + step, step)])
            new_content = re.sub(r"([A-Za-z0-9]+)-([A-Za-z0-9]+)", repl_range, content)
            return "{" + new_content + "}"
        return re.sub(r"\{([^}]+)\}", repl_bracket, text)

    def expand_brackets(self, token):
        results = [token]
        while True:
            new_results = []
            expanded_any = False
            for s in results:
                match = re.search(r"\{([^}]+)\}", s)
                if match:
                    expanded_any = True
                    prefix, content, suffix = s[:match.start()], match.group(1), s[match.end():]
                    for item in content.strip().split():
                        new_results.append(prefix + item + suffix)
                else: new_results.append(s)
            results = new_results
            if not expanded_any: break
        return results

    def process_line(self, line):
        # 1. 支持行尾注释：剔除 # 之后的内容
        raw_line = line # 保留原始行用于错误高亮
        line = line.split('#')[0].strip()
        if not line or '=' in line: return raw_line if '=' in line else None

        match = re.match(r"(\w+)\s*\((.*)\)", line)
        if not match: return None

        port_name, description = match.groups()
        
        # 2. 重复端口检测
        if port_name in self.defined_ports:
            print(f"\033[31m[Duplicate Port Error] Port '{port_name}' is defined multiple times!\033[0m")
            sys.exit(1)
        self.defined_ports.add(port_name)

        tokens = [t.strip() for t in description.split(',')]
        expanded_pins = []
        for token in tokens:
            step1 = self.expand_ranges_in_brackets(token)
            expanded_pins.extend(self.expand_brackets(step1))

        # 3. 校验与颜色高亮错误定位
        for p in expanded_pins:
            if p not in self.valid_pins:
                # 颜色高亮定位：将错误的引脚在原始行中用红底白字标出
                highlight = f"\033[41;37m {p} \033[0m"
                err_msg = raw_line.replace(p, highlight)
                print(f"\033[31m[Syntax Error] Invalid physical pin '{p}' detected!\033[0m")
                print(f"Context: {err_msg}")
                sys.exit(1)
            
            if p in self.used_pins:
                print(f"\033[31m[Conflict Error] Physical pin '{p}' is assigned to both '{self.used_pins[p]}' and '{port_name}'!\033[0m")
                sys.exit(1)
            self.used_pins[p] = port_name

        # 记录摘要信息
        self.summary.append({"port": port_name, "width": len(expanded_pins)-1, "count": len(expanded_pins)})
        return f"{port_name} ({', '.join(expanded_pins)})"

    def print_summary(self):
        if not self.summary: return
        # 4. 自动位宽对齐计算
        max_name_len = max(len(s["port"]) for s in self.summary)
        print("\n\033[32m=== Port Binding Summary ===\033[0m")
        for s in self.summary:
            name = s["port"].ljust(max_name_len)
            width = f"[{s['width']}:0]".ljust(8)
            print(f"  Port: {name}  Width: {width}  ({s['count']} pins)")
        print("\033[32m============================\033[0m\n")

    def convert(self, input_path, output_path):
        if not os.path.exists(input_path): return
        with open(input_path, 'r') as f: lines = f.readlines()

        final_lines = []
        for line in lines:
            line = line.strip()
            if not line: continue
            if line.startswith('@'):
                loop_match = re.match(r"@(\d+|[A-Z])-(\d+|[A-Z])\s+(.*)", line.split('#')[0])
                if loop_match:
                    start, end, body = loop_match.groups()
                    s_val = int(start) if start.isdigit() else ord(start)
                    e_val = int(end) if end.isdigit() else ord(end)
                    step = -1 if s_val > e_val else 1
                    for i in range(s_val, e_val + step, step):
                        current_line = body
                        for expr in re.findall(r"\[@([^\]]+)\]", current_line):
                            res_val = int(eval(f"{i}{expr}"))
                            current_line = current_line.replace(f"[@{expr}]", str(res_val))
                        processed = self.process_line(current_line.replace('@', str(i) if start.isdigit() else chr(i)))
                        if processed: final_lines.append(processed)
            else:
                processed = self.process_line(line)
                if processed: final_lines.append(processed)

        with open(output_path, 'w') as f: f.write('\n'.join(final_lines) + '\n')
        self.print_summary()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("input", nargs="?"); parser.add_argument("output", nargs="?")
    parser.add_argument("--verbose", "-v", action="store_true")
    args = parser.parse_args()
    pwd = os.path.dirname(os.path.abspath(__file__)) + "/"
    conv = NXDCConverter(pwd + "pins", verbose=args.verbose)
    conv.convert(args.input or pwd+"top.nxdclite", args.output or pwd+"top.nxdc")