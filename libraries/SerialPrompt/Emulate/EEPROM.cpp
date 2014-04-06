#include "EEPRom.h"

#include <stdio.h>

#define EEPROM_FILE "eeprom.dat"

EEPROMClass::EEPROMClass() {
	printf("Load EEPROM file");
	FILE* pFile = fopen(EEPROM_FILE, "r");
	if(!pFile) return;

	size_t read = fread(memory, 1, EEPROM_SIZE, pFile);
	fclose(pFile);
	
	printf(" (%d bytes)\n", read);
}

EEPROMClass::~EEPROMClass() {
}

uint8_t EEPROMClass::read(int address) {
	return memory[address];
}

void EEPROMClass::write(int address, uint8_t value) {
	memory[address] = value;
}

void EEPROMClass::saveToFile() {
	FILE* pFile = fopen(EEPROM_FILE, "w");
	if(!pFile) return;

	printf("Save EEPROM file");
	int written = fwrite(memory, 1, EEPROM_SIZE, pFile);
	fclose(pFile);
	printf(" (%d bytes)\n", written);
}

EEPROMClass EEPROM;
