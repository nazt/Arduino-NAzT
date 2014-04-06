#include "ConsoleListMenuIntInput.h"

ConsoleListMenuIntInput::ConsoleListMenuIntInput(const char* command, const char* description, size_t targetOffset, int minValue, int maxValue, int defaultValue)
	: ConsoleMenuIntInput(command, description, NULL, minValue, maxValue), targetOffset(targetOffset), defaultValue(defaultValue) {
}

void ConsoleListMenuIntInput::execute(int argc, char** argv) {
	ConsoleMenuIntInput::valueTarget = (int*)((uint8_t*)currentTarget + targetOffset);
	ConsoleMenuIntInput::execute(argc, argv);
}

void ConsoleListMenuIntInput::setDefaultValue(void* target) {
	int* targetValue = (int*)((uint8_t*)target + targetOffset);
	*targetValue = defaultValue;
}

void ConsoleListMenuIntInput::setInputTarget(void* target) {
	this->currentTarget = target;
}
