  .inesprg 1   ; 1x 16KB PRG code
  .ineschr 1   ; 1x  8KB CHR data
  .inesmap 0   ; mapper 0 = NROM, no bank swapping
  .inesmir 1   ; background mirroring
  
  .rsset $0000  ;;start variables at ram location 0
buttons1   .rs 1  ; player 1 gamepad buttons, one bit per button
checked    .rs 1
bullet_x   .rs 1
bullet_y   .rs 1
bullet_dx  .rs 1
bullet_active .rs 1
	
BTN_A  = %10000000
BTN_B  = %01000000
SELECT = %00100000
START  = %00010000
UP     = %00001000
DOWN   = %00000100
LEFT   = %00000010
RIGHT  = %00000001

RIGHTEDGE = $C8
LEFTEDGE = $30

;;;;;;;;;;;;;;;

    
  .bank 0
  .org $C000 

	.include "setup.inc"
	.include "load_palette.inc"

	LDA #0
	STA buttons1
	STA checked
	STA bullet_active

  LDA #$70
  STA $0200        ; put sprite 0 in center vert
  LDA #$80
  STA $0203        ; put sprite 0 in center horiz
  LDA #$00
  STA $0201        ; tile number = 0
  LDA #%00000000
  STA $0202        ; color = 0, no flipping

  LDA #$01
  STA $0205        ; tile number = 1
  LDA #%00000000
  STA $0206        ; color = 0, no flipping

	.include "load_background.inc"
	
  LDA #%10010000   ; enable NMI, sprites from Pattern Table 0
  STA $2000

  LDA #%00011110   ; enable sprites
  STA $2001

Forever:
  JMP Forever     ;jump back to Forever, infinite loop
  
 

NMI:
  LDA #$00
  STA $2003  ; set the low byte (00) of the RAM address
  LDA #$02
  STA $4014  ; set the high byte (02) of the RAM address, start the transfer

	LDA bullet_active
	BEQ BulletMoveDone
	
	LDA $0207 			; get bullet x
	CLC
	ADC bullet_dx
	STA $0207

	CMP #RIGHTEDGE
	BEQ ContinueBulletCheck
	BCS ResetBullet
ContinueBulletCheck:

	CMP #LEFTEDGE
	BCC ResetBullet
	JMP BulletMoveDone

ResetBullet:
	LDA #0
	STA bullet_active
	STA $0204
	STA $0207

BulletMoveDone:
	JSR ReadController1

	.include "reada.inc"
	.include "readb.inc"
	.include "readup.inc"
	.include "readdown.inc"
	.include "readleft.inc"
	.include "readright.inc"

	RTI        ; return from interrupt
 
	.include "get_input.inc"
	.include "draw_background.inc"
;;;;;;;;;;;;;;  
  
  .bank 1
  .org $E000
  
	.include "palette.inc"

top_bar:
  .db $1,$1,$1,$1,$1,$1,$0,$0,$0,$0,$0,$0,$0,$0,$0,$0 ; top and bottom line
  .db $0,$0,$0,$0,$0,$0,$0,$0,$0,$0,$1,$1,$1,$1,$1,$1

side_bars:
  .db $1,$1,$1,$1,$1,$1,$0,$1,$1,$1,$1,$1,$1,$1,$1,$1 ; side bars
  .db $1,$1,$1,$1,$1,$1,$1,$1,$1,$0,$1,$1,$1,$1,$1,$1
	
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
