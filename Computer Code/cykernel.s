.setcpu "65C02"
.segment "ZEROPAGE"
  WRT_PTR: .res 1           ;Input Buffer Write Pointer
  READ_PTR: .res 1          ;Input Buffer Read Pointer
  .include "zeropage.s"
.segment "STACK"
.segment "INPUT_BUFFER"
BUFFER: .res $100           ;Input Buffer
.segment "RAM"
.segment "IO"
.segment "BASIC"
  .include "msbasic.s"      ;MS Basic
.segment "KERNEL"
  .include "kernel.s"       ;Kernel
.segment "MONITOR"          
  .include "wozmon.s"       ;Includes Monitor Software
.segment "RESET"
  .word "monbas"            ;Checks for monitor or monitor key
  .word "init"              ;Initializes the hardware
  .word "irq"               ;Interrupt handler