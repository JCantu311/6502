.segment "ZEROPAGE"
.segment "STACK"
.segment "RAM"
.segment "IO"

.segment "CODE"
start:


.segment "RESET"
    .word start
    .word start 
    .word start