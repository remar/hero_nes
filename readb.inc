ReadB: 
  LDA bullet_active
  BNE ReadBDone

  LDA buttons1       ; player 1 - B
  AND #BTN_B  ; only look at bit 0
  BEQ ReadBDone

  AND checked ; if we've already checked this button, we're done
  BNE ReadBDone

  LDA checked ; save that we've checked the button
  ORA #BTN_B
  STA checked

  LDA #%01000000
  STA $0202        ; color = 0, flip left

  ; set bullet position relative to player
  LDA $0203
  SEC
  SBC #$02
  STA $0207

  LDA $0200
  CLC
  ADC #$03
  STA $0204

  LDA #1
  STA bullet_active
  LDA #$fe
  STA bullet_dx

ReadBDone:        ; handling this button is done
