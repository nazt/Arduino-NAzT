#ifndef CONFIG_H
#define CONFIG_H

#include "WProgram.h"

#define INT_MIN -32768
#define INT_MAX 32767

#define CONFIG_STRUCT_VERSION 0x0003

void load_int(int* dst, int* n);
void load_uint(unsigned int* dst, int* n);
void load_bool(bool* dst, int* n);

void save_int(int* dst, int* n);
void save_uint(unsigned int* dst, int* n);
void save_bool(bool* dst, int* n);

#endif
