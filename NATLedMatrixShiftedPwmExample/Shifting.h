#ifndef SHIFTING_H
#define SHIFTING_H

#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

#define sbipin(pin) sbi((pin)<8 ? PORTD:PORTB, (pin) - ((pin)<8 ? 0:8))
#define cbipin(pin) cbi((pin)<8 ? PORTD:PORTB, (pin) - ((pin)<8 ? 0:8))

#define bitOut(pin, val) { \
  if ((val) == LOW) cbipin(pin); \
  else              sbipin(pin); \
}

#define shiftOutBit(dataPin, clockPin, val, bit) { \
  bitOut(dataPin, ((val) & (1 << (bit))) ? HIGH:LOW); \
  bitOut(clockPin, HIGH); \
  bitOut(clockPin, LOW); \
}

#define shiftOutByte(dataPin, clockPin, bitOrder, val) { \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?0:7); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?1:6); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?2:5); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?3:4); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?4:3); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?5:2); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?6:1); \
  shiftOutBit(dataPin, clockPin, val, (bitOrder) == LSBFIRST ?7:0); \
}

#endif
