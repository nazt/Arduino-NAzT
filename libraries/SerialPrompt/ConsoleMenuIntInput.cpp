#include "ConsoleMenuIntInput.h"

#include <stdio.h>

ConsoleMenuIntInput::ConsoleMenuIntInput(const char* command, const char* description, int* valueTarget, int minValue, int maxValue)
	: ConsoleMenuInput(command, description), valueTarget(valueTarget), minValue(minValue), maxValue(maxValue) {
}

void ConsoleMenuIntInput::execute(int argc, char** argv) {
  inputBufferIndex = 0;
  inputBuffer[0] = '\0';

  bool validValue = false;
  bool negative;
  while(!validValue) {
    negative = false;

		Serial.print(description);
    Serial.print(" (");
    Serial.print(minValue);
    Serial.print(" - ");
    Serial.print(maxValue);
    Serial.print(") [");
    Serial.print(*valueTarget);
    Serial.print("]: ");

    uint8_t inputAction = readInput();
    if(inputAction == INPUT_ACT_NONE) {
    	Serial.println("Invalid action command entered!!!");
    } else if(inputAction == INPUT_ACT_RETURN) {
    	return;
    } else if(inputAction == INPUT_ACT_RETRY) {
    	// Do nothing, all handled in parent
    } else if(inputAction == INPUT_ACT_CONFIRM) {
    	printf("INPUT_ACT_CONFIRM (%d)\n", inputBufferIndex);
	    if(inputBufferIndex == 0) {
	      Serial.print("Using current value (");
	      Serial.print(*valueTarget);
	      Serial.println(")");
	      value = *valueTarget;
	      validValue = true;
	      break;
	    }
	
			int c;
	    value = 0;
	    validValue = true;
	    for(int i=0; i<inputBufferIndex; i++) {
	      c = inputBuffer[i];
	      if(c >= '0' && c <= '9') {
	        value *= 10;
	        value += c - '0';
	      }
	      else if(c == '-') {
	        if(!negative)
	          negative = true;
	        else {
	          validValue = false;
	          break;
	        }
	      }
	      else {
	        validValue = false;
	        break;
	      }
	    }
	
	    if(validValue) {
	      if(negative) value *= -1;
	      if(value < minValue || value > maxValue) validValue = false;
	    }
		  
			inputBufferIndex = 0;
			inputBuffer[0] = '\0';
	  }
  }

  Serial.print("Entered value: ");
  Serial.print(value);
  Serial.println();
  *valueTarget = value;
}


