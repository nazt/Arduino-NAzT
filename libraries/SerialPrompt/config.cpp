#include <EEPROM.h>

#include "config.h"

void load_eeprom(byte* mem, int size, int* n) {
  while(size--) {
    *mem++ = EEPROM.read((*n)++);
  }
}

void load_int(int* dst, int* n) {
  load_eeprom((byte*)dst, sizeof(int), n);
}

void load_uint(unsigned int* dst, int* n) {
  load_eeprom((byte*)dst, sizeof(unsigned int), n);
}

void load_bool(bool* dst, int* n) {
  load_eeprom((byte*)dst, sizeof(bool), n);
}

void save_eeprom(byte* mem, int size, int* n) {
  while(size--) {
    EEPROM.write((*n)++, *mem++);
  }
}

void save_int(int* dst, int* n) {
  save_eeprom((byte*)dst, sizeof(int), n);
}

void save_uint(unsigned int* dst, int* n) {
  save_eeprom((byte*)dst, sizeof(unsigned int), n);
}

void save_bool(bool* dst, int* n) {
  save_eeprom((byte*)dst, sizeof(bool), n);
}
