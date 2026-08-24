.setcpu "W65C02"
.segment "ZEROPAGE"
.segment "STACK"
.segment "RAM"
STA_INST: .res 1
ADDR_LOW: .res 1
ADDR_HIGH: .res 1
RETURN: .res 1
.segment "IO"
.segment "CODE"
init:
    LDX #$8D
    STX STA_INST
    LDX #$00
    STX ADDR_LOW
    LDX #$04
    STX ADDR_HIGH
    LDX #$60
    STX RETURN
loop:
    LDA #00         ;Reset Accumulator
    LDA #$FF
    JSR STA_INST
    INC ADDR_LOW
    BEQ next
    JMP loop
next:
    INC ADDR_HIGH
    LDA ADDR_HIGH
    CMP #$40
    BEQ exit
    JMP loop
COLD_START:
    WAI 
exit:
    JMP COLD_START
.segment "RESET"
    .word init
    .word init
    .word init
