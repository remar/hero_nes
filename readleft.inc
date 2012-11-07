ReadLeft: 
  LDA $4016       ; player 1 - Left
  AND #%00000001  ; only look at bit 0
  BEQ ReadLeftDone   ; branch to ReadADone if button is NOT pressed (0)
                  ; add instructions here to do something when button IS pressed (1)
  LDA $0203       ; load sprite Y position
  SEC             ; make sure carry flag is set
  SBC #$01        ; A = A - 1
  STA $0203       ; save sprite Y position
ReadLeftDone:        ; handling this button is done
