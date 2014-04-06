#ifndef ConsoleMenuIntInput_h
#define ConsoleMenuIntInput_h

#include "ConsoleMenuInput.h"

class ConsoleMenuIntInput : public ConsoleMenuInput {
	public:
		ConsoleMenuIntInput(const char* command, const char* description, int* valueTarget, int minValue, int maxValue);
		virtual void execute(int argc, char** argv);

	protected:
		int* valueTarget;

	private:
		int value;
		int minValue;
		int maxValue;
};

#endif
