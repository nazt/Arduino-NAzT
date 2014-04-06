#ifndef WIRING_H
#define WIRING_H

#include <inttypes.h>

#define INPUT 0x0
#define OUTPUT 0x1

#define LOW 0x0
#define HIGH 0x1

typedef uint8_t byte;

void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);
unsigned long millis();
void delay(unsigned long ms);

void init();
void setup();
void loop();

#endif
