#include "ConsoleMenuItem.h"

char inputBuffer[INPUT_SIZE + 1];
int inputBufferIndex = 0;
char NEW_LINE_CHAR = 13; // \r?

ConsoleMenuItem::ConsoleMenuItem(const char* command, const char* description) {
	this->command = command;
	this->description = description;
}

uint8_t ConsoleMenuItem::handleInputChar(char c) {
  if(c == NEW_LINE_CHAR) {
    inputBuffer[inputBufferIndex] = '\0';
    return INPUT_ACT_CONFIRM;
  }
  else if(c == 127) {
    if(inputBufferIndex > 0) {
      inputBuffer[--inputBufferIndex] = '\0';
      Serial.print(byte(127));
    }
  }
  else if(c == 3) { // Ctrl-C
    Serial.println();
    inputBufferIndex = 0;
    inputBuffer[inputBufferIndex] = '\0';
    return INPUT_ACT_RETRY;
  }
  else if(c == 4 || c == 26) { // Ctrl-D, Ctrl-Z
    Serial.println();
    return INPUT_ACT_RETURN;
  }
  else if(c == 9) { // Tab
    //inputBuffer[p++] = ' ';
    //Serial.print(' ');
  }
  else if(c >= 32 && c < 127) {
    inputBuffer[inputBufferIndex++] = c;
    Serial.print(byte(c));
  }
  else {
    Serial.println(int(c));
  }
  
  return INPUT_ACT_NONE;
}

uint8_t ConsoleMenuItem::readInput() {
	uint8_t result;
	int c;
  do {
    if(Serial.available() > 0) {
      c = Serial.read();
			if((result = handleInputChar(c)) != INPUT_ACT_NONE) {
				return result;
			}
    }
  }
  while(inputBufferIndex < INPUT_SIZE);
  
  inputBuffer[inputBufferIndex - 1] = '\0';
  return INPUT_ACT_CONFIRM;
}
