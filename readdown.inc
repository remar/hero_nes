ReadDown: 
  LDA $4016       ; player 1 - Up
  AND #%00000001  ; only look at bit 0
  BEQ ReadDownDone   ; branch to ReadADone if button is NOT pressed (0)
                  ; add instructions here to do something when button IS pressed (1)
  LDA $0200       ; load sprite Y position
  CLC             ; make sure carry flag is set
  ADC #$01        ; A = A + 1
  STA $0200       ; save sprite Y position
ReadDownDone:        ; handling this button is done
