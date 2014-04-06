#include "ConsoleMenuInput.h"

extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

ConsoleMenuInput::ConsoleMenuInput(const char* command, const char* description)
	: ConsoleMenuItem(command, description) {
}
