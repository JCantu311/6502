.segment "ZEROPAGE"
num1: .res 1
op: .res 1
num2: .res 1
ans: .res 1
buffer: .res 1
loop: .res 1
.segment "STACK"
.segment "RAM"
.segment "IO"
.segment "CODE"
inputs:           ;Load the numbers and operator into the registers
    LDA #00
    STA num1
    LDA #$2D
    STA op
    LDA #00
    STA num2
    LDX num1
    LDY num2
    LDA op
calculation:
    CMP #$2B
    BEQ add
    CMP #$2D
    BEQ subtract
    CMP #$2A
    BEQ multiply
    CMP #$2F
    BEQ divide
add:
    CLC
    PHA
    TXA
    ADC num2
    STA ans
    PLA
    JMP break
subtract:
    SEC
    LDA num1
    SBC num2
    STA ans
    JMP break
multiply:
    LDA #0
    STA ans
    LDA num1
    BEQ multbrk
    LDA num2
    BEQ multbrk
    STA loop
multloop:
    CLC
    LDA ans
    ADC num1
    STA ans
    DEC loop
    BNE multloop
multbrk:
    JMP break
divide:
    CLC
    PHA
    LDA num2
    BEQ divzero
    LDA num1
    CMP num2
    BEQ divsame
    LDA #0
    STA loop
    PLA
    JSR divloop
divloop:
    PHA
    LDA loop
    CMP #8
    BEQ divbrk
    ASL num1
    ROL ans
    LDA ans
    CMP num2
    BCC skip
    SBC num2
    STA ans
    INC num1
skip:
    INC loop
    JMP divloop
divbrk:
    LDA num1
    STA ans
    RTS
divzero:
    LDA #$FF
    STA ans
    JMP break
divsame:
    LDA #1
    STA ans
    JMP break
break:
    BRK
.segment "RESET"
    .word inputs
    .word inputs 
    .word inputs