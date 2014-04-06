#include <TimerOne.h>

#include "Shifting.h"
#include "animation.h"

#define PWM_LEVELS 4

int clockPin = 2;
int latchPin = 4;
int dataPin = 8;

int timerDelay = 1400;
byte pwmCounter = 0;
byte brightnesses[64];

void iProcess() {
  int rowOn, colsOn, c;
  for(int r=0; r<8; ++r) {
    rowOn = ~(1<<r);
    colsOn = 0;
    for(c=0; c<8; ++c) {
      colsOn |= (pwmCounter < brightnesses[r * 8 + c])<<c;
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
    for(int i=0; i<(8*8); ++i) {
      brightnesses[i] = (animation[animationIndex][i/4] >> (i%4*2)) & B00000011;
    }
  }
}
