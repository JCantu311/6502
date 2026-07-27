.segment "ZEROPAGE"
.segment "STACK"
.segment "RAM"
.segment "IO"
.segment "CODE"
start:
    LDX #$00
    STX $00
    LDX #$01
    STX $01
    LDX #$F0
    STX $02
loop:
    LDY $00
    LDX $01
    LDA #$00
    LDA #$65
    STA $0300, y
    LDA #$02
    STA $0300, x
    INC $00
    INC $01
    LDA $02
    CMP $00
    BEQ exit
    INC $00
    INC $01
    LDA $02
    CMP $00
    BEQ exit
    JMP loop
exit:
    BRK
.segment "RESET"
    .word start
    .word start
    .word start