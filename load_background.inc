LoadBackground:
	LDA $2002             ; read PPU status to reset the high/low latch
	LDA #$20
	STA $2006             ; write the high byte of $2000 address
	LDA #$00
	STA $2006             ; write the low byte of $2000 address

	LDY #$05
FirstFiveRowsLoop:
	JSR DrawBlackLine
	DEY
	BNE FirstFiveRowsLoop

	JSR DrawBar

	LDY #$12
DrawBarsLoop:
	JSR DrawSideBar
	DEY
	BNE DrawBarsLoop

	JSR DrawBar

	LDY #$05
LastFiveRowsLoop:
	JSR DrawBlackLine
	DEY
	BNE LastFiveRowsLoop
