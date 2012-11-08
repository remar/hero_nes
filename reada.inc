ReadA: 
  LDA buttons1       ; player 1 - A
  AND #BTN_A  ; only look at bit 0
  BEQ ReadADone   ; branch to ReadADone if button is NOT pressed (0)
                  ; add instructions here to do something when button IS pressed (1)
  LDA #%01000000
  STA $0202        ; color = 0, no flipping
ReadADone:        ; handling this button is done
