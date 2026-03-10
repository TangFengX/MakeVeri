import chisel3._


object ToVerilog extends App {
  circt.stage.ChiselStage.emitSystemVerilogFile(
    new top(), 
    Array("--target-dir", "generated")
  )
}