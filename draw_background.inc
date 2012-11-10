DrawBlackLine:
  LDX #$00              ; start out at 0
LoadBlackLineLoop:
  LDA #1
  STA $2007             ; write to PPU
  INX                   ; X = X + 1
  CPX #$20              ; Compare X to hex $20, decimal 32 - copying 32 bytes
  BNE LoadBlackLineLoop ; Branch to LoadBlackLine if compare was Not Equal to zero
                        ; if compare was equal to 128, keep going down
  RTS

DrawBar:
  LDX #$00              ; start out at 0
DrawBarLoop:
  LDA top_bar, x
  STA $2007             ; write to PPU
  INX                   ; X = X + 1
  CPX #$20              ; Compare X to hex $20, decimal 32 - copying 32 bytes
  BNE DrawBarLoop 	; Branch to LoadBlackLine if compare was Not Equal to zero
                        ; if compare was equal to 128, keep going down
  RTS

DrawSideBar:
  LDX #$00              ; start out at 0
DrawSideBarLoop:
  LDA side_bars, x
  STA $2007             ; write to PPU
  INX                   ; X = X + 1
  CPX #$20              ; Compare X to hex $20, decimal 32 - copying 32 bytes
  BNE DrawSideBarLoop 	; Branch to LoadBlackLine if compare was Not Equal to zero
                        ; if compare was equal to 128, keep going down
  RTS
