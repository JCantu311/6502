.segment "ZEROPAGE"
.segment "STACK"
.segment "RAM"
.segment "IO"
.segment "CODE"
start:
    LDX #$00         ; Load X index variable to zeropage
    STX $00
    LDX #$01         ; Load Y index variable to zeropage
    STX $01
    LDX #$F0         ; Load loop counter to zeropage
    STX $02
loop:
    LDX $00          ; Load X index variable from zeropage
    LDY $01          ; Load Y index variable from zeropage
    LDA #$00         ; Reset accumulator
    LDA #$65         ; Load "65" into accumulator
    STA $0300, x     ; Store "65" into memory at $0300 + X
    LDA #$02         ; Load "02" into accumulator
    STA $0300, y     ; Store "02" into memory at $0300 + Y
    INC $00          ; Increment X index variable
    INC $01          ; Increment Y index variable
    LDA $02          ; Load loop counter from zeropage
    CMP $00          ; Compare loop counter with X index variable
    BEQ exit         ; If equal, exit loop
    INC $00          ; Increment X index variable, again
    INC $01          ; Increment Y index variable, again
    LDA $02          ; Load loop counter from zeropage, again
    CMP $00          ; Compare loop counter with X index variable, again
    BEQ exit         ; If equal, exit loop
    JMP loop         ; Return to loop
exit:
    BRK
.segment "RESET"
    .word start
    .word start
    .word start