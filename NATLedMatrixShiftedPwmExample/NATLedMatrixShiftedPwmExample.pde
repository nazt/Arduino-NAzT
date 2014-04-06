#include <TimerOne.h>

#include "Shifting.h"
#include "animation.h"

#define PWM_LEVELS 16
#define ROWS 8
#define COLS 8
#define BITS_PER_PIXEL 4
#define BIT_MASK B00001111
#define PIXELS_PER_BYTE 2

int clockPin = 2;
int latchPin = 4;
int dataPin = 8;

int timerDelay = 1400;
byte pwmCounter = 0;
byte brightnesses[ROWS*COLS];

void iProcess() {
  int rowOn, colsOn, c;
  for(int r=0; r<ROWS; ++r) {
    rowOn = ~(1<<r);
    colsOn = 0;
    for(c=0; c<COLS; ++c) {
      colsOn |= (pwmCounter < brightnesses[r * COLS + c])<<c;
    }
  
    shiftOutByte(dataPin, clockPin, MSBFIRST, rowOn);
    shiftOutByte(dataPin, clockPin, MSBFIRST, colsOn);
    bitOut(latchPin, LOW);
    bitOut(latchPin, HIGH);

    if(++pwmCounter > PWM_LEVELS) pwmCounter = 0;
  }
}

void setup() {
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Timer1.initialize(timerDelay);
  Timer1.attachInterrupt(iProcess);
}

unsigned long nextImage = 0;
int animationIndex = -1;

void loop() {
  if(millis() > nextImage) {
    if(++animationIndex >= animationFrames) animationIndex = 0;
    nextImage = millis() + animationDelays[animationIndex];
    for(int i=0; i<(ROWS*COLS); ++i) {
      brightnesses[i] = (animation[animationIndex][i / PIXELS_PER_BYTE] >> (i % PIXELS_PER_BYTE * BITS_PER_PIXEL)) & BIT_MASK;
    }
  }
}
