; TODO how do we read only controller 1?
  LDA #$01
  STA $4016
  LDA #$00
  STA $4016       ; tell both the controllers to latch buttons

	LDA $4016 		; A
	LDA $4016 		; B
	LDA $4016 		; Select
	LDA $4016 		; Start

  .include "readup.inc"
  .include "readdown.inc"
  .include "readleft.inc"
  .include "readright.inc"
