  .inesprg 1   ; 1x 16KB PRG code
  .ineschr 1   ; 1x  8KB CHR data
  .inesmap 0   ; mapper 0 = NROM, no bank swapping
  .inesmir 1   ; background mirroring
  
  .rsset $0000  ;;start variables at ram location 0
buttons1   .rs 1  ; player 1 gamepad buttons, one bit per button

BTN_A = %10000000
BTN_B = %01000000
UP    = %00001000
DOWN  = %00000100
LEFT  = %00000010
RIGHT = %00000001
;;;;;;;;;;;;;;;

    
  .bank 0
  .org $C000 

	.include "setup.inc"
	.include "load_palette.inc"


  LDA #$80
  STA $0200        ; put sprite 0 in center ($80) of screen vert
  STA $0203        ; put sprite 0 in center ($80) of screen horiz
  LDA #$00
  STA $0201        ; tile number = 0
  LDA #%00000000
  STA $0202        ; color = 0, no flipping

  LDA #$60
  STA $0204        ; put sprite 1 at $60 vert
  STA $0207        ; put sprite 1 at $60 horiz
  LDA #$01
  STA $0205        ; tile number = 1
  LDA #%00000000
  STA $0206        ; color = 0, no flipping

  LDA #%10000000   ; enable NMI, sprites from Pattern Table 0
  STA $2000

  LDA #%00010000   ; enable sprites
  STA $2001

Forever:
  JMP Forever     ;jump back to Forever, infinite loop
  
 

NMI:
  LDA #$00
  STA $2003  ; set the low byte (00) of the RAM address
  LDA #$02
  STA $4014  ; set the high byte (02) of the RAM address, start the transfer

	LDA $0207 			; get bullet x
	CLC
	ADC #$02
	STA $0207

	JSR ReadController1

	.include "reada.inc"
	.include "readb.inc"
	.include "readup.inc"
	.include "readdown.inc"
	.include "readleft.inc"
	.include "readright.inc"

	RTI        ; return from interrupt
 
	.include "get_input.inc"
	
;;;;;;;;;;;;;;  
  
  .bank 1
  .org $E000
  
	.include "palette.inc"


  .org $FFFA     ;first of the three vectors starts here
  .dw NMI        ;when an NMI happens (once per frame if enabled) the 
                   ;processor will jump to the label NMI:
  .dw RESET      ;when the processor first turns on or is reset, it will jump
                   ;to the label RESET:
  .dw 0          ;external interrupt IRQ is not used in this tutorial

;;;;;;;;;;;;;;  
  
  
  .bank 2
  .org $0000
  .incbin "hero.chr"   ;includes 8KB graphics file
