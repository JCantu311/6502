.segment "KERNEL"
keyboard1 = $B001
DDRkeyboard1 = $B003
DDRps2 = $B002
VIA0IFR = $B00D
VIA0IER = $B00E
mon = #%11100000
bas = #%11100010
  init:
    LDA #%00000000
    STA DDRkeyboard1
    STA DDRps2
    LDA #%11111111
    STA VIA0IER
  monbas:
    LDA keyboard1
    CMP mon 
    BEQ COLD_START
    CMP bas
    BEQ WOZMON
  irq:
    LDA VIA0IFR
    AND #%00000010
    BEQ KEYBOARD_1
    AND #%00010000
    BEQ KEYBOARD_2
    
    RTI