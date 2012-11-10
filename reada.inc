ReadA: 
  LDA bullet_active
  BNE ReadADone

  LDA buttons1     ; player 1 - A
  AND #BTN_A       ; only look at bit 0
  BEQ ReadADone

  AND checked      ; if we've already checked this button, we're done
  BNE ReadADone

  LDA checked      ; save that we've checked the button
  ORA #BTN_A
  STA checked

  LDA #%00000000
  STA $0202        ; color = 0, no flipping

  ; set bullet position relative to player
  LDA $0203
  CLC
  ADC #$08
  STA $0207

  LDA $0200
  CLC
  ADC #$03
  STA $0204

  LDA #1
  STA bullet_active
  LDA #2
  STA bullet_dx

ReadADone:        ; handling this button is done
