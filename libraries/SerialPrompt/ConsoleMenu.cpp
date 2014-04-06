#include "ConsoleMenu.h"

#include <stdio.h>
#include <string.h>

bool starts_with(const char* haystack, const char* needle) {
  while(*haystack == *needle) {
    if(*needle == '\0') return true;
    haystack++;
    needle++;
  }

  if(*needle == '\0') return true;
  if(*needle == ' ') return true;
  if(*haystack == '\0') return false;

  return false;
}

ConsoleMenu::ConsoleMenu(const char* command, const char* title, const char* description)
:
ConsoleMenuItem(command, description), menuItemCount(0), menuItems(NULL) {
  this->title = title;
}

void ConsoleMenu::listCommands(char* prefix) {
  Serial.println("Commands:");

  for(int i=0; i<menuItemCount; i++) {
    ConsoleMenuItem* mi = menuItems[i];
    if(starts_with(mi->command, prefix)) {
      Serial.print(mi->command);
      Serial.print("\t");
      Serial.print(mi->description);
      Serial.println();
    }
  }
}

void ConsoleMenu::executeMenuItem(ConsoleMenuItem* menuItem) {
  int argc = 0;
  char* argv[MAX_ARGUMENTS];

  char* pch;
  pch = strtok(inputBuffer, " ");

  if(pch != NULL) {
    // Skip first word, this was the action not an argument
    pch = strtok(NULL, " ");

    while(pch != NULL) {
      argv[argc++] = pch;
      pch = strtok(NULL, " ");
      if(argc >= MAX_ARGUMENTS) break;
    }
  }

  menuItem->execute(argc, argv);
}

uint8_t ConsoleMenu::handleInputChar(char c) {
	if(c == '?') {
    inputBuffer[inputBufferIndex] = '\0';
    Serial.println();
    listCommands(inputBuffer);
    Serial.print(title);
    Serial.print("> ");
    Serial.print(inputBuffer);
    
    return INPUT_ACT_NONE;
  } else {
  	return ConsoleMenuItem::handleInputChar(c);
  }
}

void ConsoleMenu::execute(int argc, char** argv) {
  inputBufferIndex = 0;
  inputBuffer[0] = '\0';
  for(;;) {
    Serial.print(title);
    Serial.print("> ");
    Serial.print(inputBuffer);

    uint8_t inputAction = readInput();
    if(inputAction == INPUT_ACT_NONE) {
    	Serial.println("Invalid action command entered!!!");
    } else if(inputAction == INPUT_ACT_RETURN) {
    	return;
    } else if(inputAction == INPUT_ACT_RETRY) {
    	// Do nothing, all handled in parent
    } else if(inputAction == INPUT_ACT_CONFIRM) {
    	bool resetInput = handleInputBuffer();
    	if(resetInput) {
    		inputBufferIndex = 0;
      	inputBuffer[0] = '\0';
      }
    }
  }
}

bool ConsoleMenu::handleInputBuffer() {
	bool resetInput = false;
  bool executed = false;
  int candidates = 0;

  ConsoleMenuItem* firstCandidate = NULL;
  for(int i=0; i<menuItemCount; i++) {
    ConsoleMenuItem* mi = menuItems[i];
    if(starts_with(mi->command, inputBuffer)) {
      if(candidates++ == 0) firstCandidate = mi;
    }
  }

  if(!executed) { // If we didn't autocomplete
    if(candidates == 1) { // and we only have one matching candidate
      Serial.println();
      executeMenuItem(firstCandidate);
      resetInput = true;
      executed = true;
    }
    else if(candidates > 1) { // or, if we have more than 1 candidate
      if(strcmp(firstCandidate->command, inputBuffer) == 0) { // look for a perfect match (assumes the items are in lexiographical order)
        Serial.println();
        executeMenuItem(firstCandidate);
      resetInput = true;
        executed = true;
      }
      else { // list all options
        Serial.println();
        Serial.println("Ambiguous command");
        executed = true;
      }
    }
  }

  if(!executed && strcmp("exit", inputBuffer) == 0) { // If the user entered 'exit'
    Serial.println();
    executed = true;
    resetInput = true;
  }

  if(!executed) {
    Serial.println();
    Serial.println("Unknown command"); // don't know what they want
    executed = true;
    resetInput = true;
  }
  
  return resetInput;
}




