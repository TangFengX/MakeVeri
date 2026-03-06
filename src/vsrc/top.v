module top(
  input ps2_clk,ps2_dat,rst_n,
  output reg [13:0] ascii_seg,code_seg,counter_seg,
  output reg [1:0] state
);
  wire finish;
  wire [7:0] code,ascii;
  parameter wait_=2'b00,pressed_=2'b01,break_=2'b10;
  reg [7:0] make_code;
  reg [3:0] seg_ena;
  reg [7:0] counter;

  ps2_keyboard u_ps2_keyboard(
    .ps2_clk(ps2_clk),
    .ps2_dat(ps2_dat),
    .rst_n(rst_n),
    .finish(finish),
    .data(code)
  );
  ps2_to_ascii u_ps2_to_ascii(
    .scancode(make_code),
    .ascii(ascii)
  );

  hex_to_seg ash(
    .ena(seg_ena[3]),
    .hex(ascii[7:4]),
    .seg(ascii_seg[13:7])
  );
  hex_to_seg asl(
    .ena(seg_ena[2]),
    .hex(ascii[3:0]),
    .seg(ascii_seg[6:0])
  );
  hex_to_seg csh(
    .ena(seg_ena[1]),
    .hex(make_code[7:4]),
    .seg(code_seg[13:7])
  );

  hex_to_seg csl(
    .ena(seg_ena[0]),
    .hex(make_code[3:0]),
    .seg(code_seg[6:0])
  );

  hex_to_seg cosh(
    .ena(1'b1),
    .hex(counter[7:4]),
    .seg(counter_seg[13:7])
  );
  hex_to_seg cosl(
    .ena(1'b1),
    .hex(counter[3:0]),
    .seg(counter_seg[6:0])
  );
  always@(posedge finish or negedge rst_n) begin
    if(~rst_n)begin
      state<=2'b0;
      seg_ena<=4'b0;
      counter<=0;
    end
    else begin
      if(state==wait_)begin
        if(code!=8'hf0)begin
          state<=pressed_;
          make_code<=code;
          counter<=counter+1;
          seg_ena<=4'hf;
        end 
      end
      else if(state==pressed_)begin
        if(code==8'hf0)begin
          state<=break_;
        end
      end
      else if(state==break_)begin
        if(make_code==code) begin
          state<=wait_;
          seg_ena<=4'b0;
        end
        else begin
          state<=pressed_;
        end
      end
    end
  end

  
endmodule



module ps2_keyboard(
  input ps2_clk,ps2_dat,rst_n,
  output reg finish,
  output reg [7:0] data 
);
  reg [3:0] counter;
  always@(negedge ps2_clk or negedge rst_n)begin
    if(rst_n)begin
      if(counter==4'b0& ~ps2_dat) counter<=4'd1;
      else if (counter>4'd0 & counter <4'd9) begin
        data[counter-1]<=ps2_dat;
        finish<=0;
        counter<=counter+4'd1;
      end 
      else if (counter==4'd9) begin
        if(^{data,ps2_dat}) counter<=0;
        else begin 
          
          counter<=4'd0;
          finish<=1'b1;
        end
      end
      else counter<=4'd0;
    end
    else begin 
      counter<=4'd0;
      finish<=1'b0;
    end
  end
endmodule



module hex_to_seg(
    input      ena,
    input      [3:0] hex,    // 4位十六进制输入 (0-15)
    output reg [6:0] seg     // 7位段码输出 {g, f, e, d, c, b, a}
);

    always @(*) begin
      if(ena)begin
        case(hex)
            4'h0: seg = 7'b1000000; // 0
            4'h1: seg = 7'b1111001; // 1
            4'h2: seg = 7'b0100100; // 2
            4'h3: seg = 7'b0110000; // 3
            4'h4: seg = 7'b0011001; // 4
            4'h5: seg = 7'b0010010; // 5
            4'h6: seg = 7'b0000010; // 6
            4'h7: seg = 7'b1111000; // 7
            4'h8: seg = 7'b0000000; // 8
            4'h9: seg = 7'b0010000; // 9
            4'hA: seg = 7'b0001000; // A
            4'hB: seg = 7'b0000011; // b
            4'hC: seg = 7'b1000110; // C
            4'hD: seg = 7'b0100001; // d
            4'hE: seg = 7'b0000110; // E
            4'hF: seg = 7'b0001110; // F
            default: seg = 7'b1111111; // 全灭
        endcase
      end
      else seg=~7'b0;
        
    end

endmodule


module ps2_to_ascii(
    input      [7:0] scancode, // PS/2 扫描码输入
    output reg [7:0] ascii     // ASCII 码输出
);

    always @(*) begin
        case(scancode)
            // 数字键 (大键盘区)
            8'h45: ascii = 8'h30; // 0
            8'h16: ascii = 8'h31; // 1
            8'h1E: ascii = 8'h32; // 2
            8'h26: ascii = 8'h33; // 3
            8'h25: ascii = 8'h34; // 4
            8'h2E: ascii = 8'h35; // 5
            8'h36: ascii = 8'h36; // 6
            8'h3D: ascii = 8'h37; // 7
            8'h3E: ascii = 8'h38; // 8
            8'h46: ascii = 8'h39; // 9

            // 字母键 (映射为大写 ASCII)
            8'h1C: ascii = 8'h41; // A
            8'h32: ascii = 8'h42; // B
            8'h21: ascii = 8'h43; // C
            8'h23: ascii = 8'h44; // D
            8'h24: ascii = 8'h45; // E
            8'h2B: ascii = 8'h46; // F
            8'h34: ascii = 8'h47; // G
            8'h33: ascii = 8'h48; // H
            8'h43: ascii = 8'h49; // I
            8'h3B: ascii = 8'h4A; // J
            8'h42: ascii = 8'h4B; // K
            8'h4B: ascii = 8'h4C; // L
            8'h3A: ascii = 8'h4D; // M
            8'h31: ascii = 8'h4E; // N
            8'h44: ascii = 8'h4F; // O
            8'h4D: ascii = 8'h50; // P
            8'h15: ascii = 8'h51; // Q
            8'h2D: ascii = 8'h52; // R
            8'h1B: ascii = 8'h53; // S
            8'h2C: ascii = 8'h54; // T
            8'h3C: ascii = 8'h55; // U
            8'h2A: ascii = 8'h56; // V
            8'h1D: ascii = 8'h57; // W
            8'h22: ascii = 8'h58; // X
            8'h35: ascii = 8'h59; // Y
            8'h1A: ascii = 8'h5A; // Z

            // 常用字符与控制键
            8'h29: ascii = 8'h20; // Space (空格)
            8'h5A: ascii = 8'h0D; // Enter (回车, ASCII CR)
            8'h66: ascii = 8'h08; // Backspace (退格)
            8'h0E: ascii = 8'h60; // ` (反引号)
            8'h4E: ascii = 8'h2D; // - (减号)
            8'h55: ascii = 8'h3D; // = (等号)
            8'h54: ascii = 8'h5B; // [
            8'h5B: ascii = 8'h5D; // ]
            8'h5D: ascii = 8'h5C; // \
            8'h4C: ascii = 8'h3B; // ;
            8'h52: ascii = 8'h27; // '
            8'h41: ascii = 8'h2C; // ,
            8'h49: ascii = 8'h2E; // .
            8'h4A: ascii = 8'h2F; // /

            // 默认值
            default: ascii = 8'h00; // 未知键码输出空字符
        endcase
    end

endmodule






