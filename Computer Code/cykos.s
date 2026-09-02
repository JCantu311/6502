.setcpu "65C02"
; Source code for the Cykomputer Model 2610 Kernel
; Included software: MS Basic
;                    Resident System Monitor
;                    Kernel
; RAM is mapped as thus:
; 1.   Zeropage:                                      $0000-$00FF
; 2.   Stack:                                         $0100-$01FF
; 3.   Input Buffer:                                  $0200-$02FF
; 4.   Usable Ram:                                    $0300-$AFFF

; I/O Devices mapped as thus:
; 1.   Keyboard controller:                           $B000-$B00F
; 2.   Banking, timer, and video address controller:  $B010-$B01F
; 3.   SPI Cartridge Controller:                      $B020-$B02F
; 4.   Sound Chip:                                    $B030-$B04F
; 5.   RS-232 Port 1:                                 $B050-$B053
; 6.   USB Port:                                      $B054-$B057
; 7.   RS-232 Port 2:                                 $B058-$B05B
; 8.   Parallel Cartridge:                            $B05C-$B444
; 9.   Expansion Slot 1:                              $B445-$B82D
; 10.  Expansion Slot 2:                              $B82E-$BC16
; 11.  Expansion Slot 3:                              $BC17-$BFFF
; I/O Devices 1-3 are controlled by W65C22 VIA Chips, consult datasheet for exact addresses
; I/O Device 4 is a standard MOS Technology 6581 Chip or a pin-compatible replacement, consult datasheet for exact addresses
;     NOTE: The address space allocated to the 6581 is 3 bytes larger than the 6581 requires, this is to simplify address decoding logic. 
;           Avoid using addresses $B04D-$B04F as the chip does not use these and may cause issues with the chip or compatibles. 
;           Some compatibles may use these addresses, consult datasheet of your choice in sound chip for any information
; I/O Devices 5-7 are controlled by W65C51 ACIA Chips, consult datasheet for exact addresses
;     NOTE: There is a known issue regarding the W65C51 ACIA Status register where the ready bit is always set to true, adjust code accordingly
; I/O Devices 8-11 are controlled by devices TBD by manufacturers, consult datasheets and/or contact manufacturers for any information.
;     NOTE: Each expansion slot has a total of 1001 addresses, however it is possible to change addresses to accomodate any differences in hardware.
;           The 1001 allocated addresses is simply a recommendation that will not be recognized by the Kernel. 

; ROM is mapped as thus:
; 1.   MS Basic:                                      $C000-$DFFF
; 2.   Kernel:                                        $EFFF-$FEFF
; 3.   System Monitor:                                $FF00-$FFF9
; 4.   NMI/Reset/IRQ Vectors:                         $FFFA-$FFFF
.segment "ZEROPAGE"
  WRT_PTR: .res 1           ;Input Buffer Write Pointer
  READ_PTR: .res 1          ;Input Buffer Read Pointer
  BUFFER_SIZE: .res 1       ;Input Buffer Size
  .include "zeropage.s"
.segment "STACK"
.segment "INPUT_BUFFER"
BUFFER: .res $100           ;Input Buffer

.segment "RAM"
.segment "IO"
.segment "BASIC"
  .include "msbasic.s"      ;MS Basic
.segment "KERNEL"
  .include "kernel.s"       ;Kernel
.segment "MONITOR"          
  .include "wozmon.s"       ;Monitor Software
.segment "RESET"
  .word monbas              ;Checks for monitor or monitor key
  .word init                ;Initializes the hardware
  .word irq                 ;Interrupt handler