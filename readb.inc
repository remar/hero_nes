ReadB: 
  LDA buttons1       ; player 1 - B
  AND #BTN_B  ; only look at bit 0
  BEQ ReadBDone   ; branch to ReadBDone if button is NOT pressed (0)
                  ; add instructions here to do something when button IS pressed (1)
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

ReadBDone:        ; handling this button is done
