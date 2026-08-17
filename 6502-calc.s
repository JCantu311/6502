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
    LDA #00       ;num1
    STA num1
    LDA #$2D      ;op
    STA op
    LDA #00       ;num2
    STA num2
    LDX num1
    LDY num2
    LDA op
calculation:
    CMP #$2B      ;Check if operator = "+"
    BEQ add
    CMP #$2D      ;Check if operator = "-"
    BEQ subtract
    CMP #$2A      ;Check if operator = "*"
    BEQ multiply
    CMP #$2F      ;Check if operator = "/"
    BEQ divide
add:              ;Addition initialization
    CLC           ;Clear Carry Flag
    PHA           ;Push accumulator to stack
    TXA           ;Move num1 from X to accumulator
    ADC num2      ;Add num1 and num2
    STA ans       ;Store answer to "ans" variable
    PLA           ;Pull from stack
    JMP break     ;Jump to break label
subtract:         ;Subtraction initialization
    SEC           ;Set carry flag
    LDA num1      ;Load num1 to accumulator
    SBC num2      ;Subtract num2 from num1
    STA ans       ;Store answer to "ans"
    JMP break     ;Break
multiply:         ;Initialize multiplication 
    LDA #0        ;Load number "0" to accumulator
    STA ans       ;Store to "ans"
    LDA num1      ;Load num1 to accumulator
    BEQ multbrk   ;Jump to break if num1 = 0
    LDA num2      ;Load num2 into accumulator
    BEQ multbrk   ;Jump to break if num2 = 0
    STA loop      ;Store num2 to loop variable
multloop:         ;Multiplication loop
    CLC           ;Clear carry flag
    LDA ans       ;Load 0 from ans variable
    ADC num1      ;Add num1 to accumulator
    STA ans       ;Store to ans
    DEC loop      ;Decrement loop variable
    BNE multloop  ;Continue looping if loop doesn't equal zero
multbrk:          ;End multiplication
    JMP break     ;Jump to break
divide:           ;Division subroutine
    CLC           ;Clear carry flag
    PHA           ;Push accumulator to stack
    LDA num2      ;Load num2 into accumulator
    BEQ divzero   ;Jump to divzero if num2 = 0
    LDA num1      ;Load num1 into accumulator
    CMP num2      ;Compare num1 to num2
    BEQ divsame   ;Jump to divsame if num1 = num2
    LDA #0        ;Load 0 into accumulator
    STA loop      ;Store 0 into loop variable
    PLA           ;Pull from stack
    JSR divloop   ;Jump to divloop subroutine
divloop:          ;Loop for dividing
    PHA           ;Push accumulator to stack
    LDA loop      ;Load loop into accumulator
    CMP #8        ;Compare with 8
    BEQ divbrk    ;Jump to divbrk if accumulator = 8
    ASL num1      ;Arithmetically Shift num1 bits to left
    ROL ans       ;Rotates bits to left
    LDA ans       ;Load ans into accumulator
    CMP num2      ;Compare ans with num2
    BCC skip      ;Jump to skip if carry flag is clear
    SBC num2      ;Subtract num2 from accumulator
    STA ans       ;Store accumulator to ans
    INC num1      ;Increment num1
skip:             ;Skip division number
    INC loop      ;Increment loop counter
    JMP divloop   ;Jump back to divloop
divbrk:           ;End division
    LDA num1      ;Load num1 into accumulator
    STA ans       ;Store accumulator to ans
    RTS           ;Return from subroutine
divzero:          ;num1 or num2 equal 0
    LDA #$FF      ;Load $FF hex (255 decimal, representing undefined) into accumulator
    STA ans       ;Store accumulator to ans
    JMP break     ;Jump to break
divsame:          ;num1 and num2 are equal
    LDA #1        ;Load decimal 1 to accumulator
    STA ans       ;Store accumulator to ans
    JMP break     ;Jump to break
break:            ;End calculations
    BRK           ;Break
.segment "RESET"
    .word inputs
    .word inputs 
    .word inputs