ReadRight: 
  LDA buttons1       ; player 1 - Left
  AND #RIGHT  ; only look at bit 0
  BEQ ReadRightDone   ; branch to ReadADone if button is NOT pressed (0)
                  ; add instructions here to do something when button IS pressed (1)
  LDA $0203       ; load sprite Y position
  CLC             ; make sure carry flag is cleared
  ADC #$01        ; A = A + 1
  STA $0203       ; save sprite Y position
ReadRightDone:        ; handling this button is done
