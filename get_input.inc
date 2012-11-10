ReadController1:
  LDA buttons1     ; save old buttons
  PHA

  LDA #$01
  STA $4016
  LDA #$00
  STA $4016
  LDX #$08
ReadController1Loop:
  LDA $4016
  LSR A            ; bit0 -> Carry
  ROL buttons1     ; bit0 <- Carry
  DEX
  BNE ReadController1Loop

  PLA              ; load old buttons1 in A
  EOR buttons1     ; XOR with current buttons1
  EOR #$ff         ; invert
  AND checked      ; uncheck bits for input that changed
  STA checked

  RTS
