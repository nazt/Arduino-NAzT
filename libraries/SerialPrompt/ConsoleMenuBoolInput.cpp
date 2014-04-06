#include "ConsoleMenuBoolInput.h"

#include <stdio.h>

ConsoleMenuBoolInput::ConsoleMenuBoolInput(const char* command, const char* description, bool* valueTarget)
	: ConsoleMenuInput(command, description), valueTarget(valueTarget) {
}

void ConsoleMenuBoolInput::execute(int argc, char** argv) {
  bool validValue = false;
  while(!validValue) {
    validValue = false;

    Serial.print("Enter value (y/n) [");
    Serial.print(b2c(*valueTarget));
    Serial.print("]: ");
    int p = 0;
    int c;

    do {
      if(Serial.available()) {
        c = Serial.read();
        if(c == NEW_LINE_CHAR) {
          inputBuffer[p] = '\0';
          Serial.println();
          break;
        }

        Serial.print((byte)c);
        inputBuffer[p++] = c;
      }
    }
    while(p < INPUT_SIZE);

    if(p == 0) {
      Serial.print("Using current value (");
      Serial.print(b2c(*valueTarget));
      Serial.println(")");
      value = *valueTarget;
      validValue = true;
      break;
    }
    else if(p == 1) {
      switch(inputBuffer[0]) {
      case 'y':
      case 'Y':
        value = true;
        validValue = true;
        break;
      case 'n':
      case 'N':
        value = false;
        validValue = true;
        break;
      default:
        validValue = false;
        break;
      }
    }
  }

  Serial.print("Entered value: ");
  Serial.print(b2c(value));
  Serial.println();
	*valueTarget = value;
}

