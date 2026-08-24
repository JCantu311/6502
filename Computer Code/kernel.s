.segment "KERNEL"
  init:
    NOP
  monbas:
    LDA keyboard1
    CMP mon 
    BEQ COLD_START
    CMP bas
    BEQ WOZMON
  irq:
    