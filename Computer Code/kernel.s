.segment "KERNEL"
keyboard1 = $B001
DDRkeyboard1 = $B003
DDRps2 = $B002
mon = #%11100000
bas = #%11100010
  init:
    LDA %00000000
    STA DDRkeyboard1
    STA DDRps2
  monbas:
    LDA keyboard1
    CMP mon 
    BEQ COLD_START
    CMP bas
    BEQ WOZMON
  irq:
    LDA 