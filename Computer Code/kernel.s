.segment "KERNEL"
  init:
    NOP
  monbas:
    LDA keyboard1
    CMP mon 
    BEQ COLD_START