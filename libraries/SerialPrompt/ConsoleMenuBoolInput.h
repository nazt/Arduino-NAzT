#ifndef ConsoleMenuBoolInput_h
#define ConsoleMenuBoolInput_h

#include "ConsoleMenuInput.h"

#define b2c(b) (b?'Y':'N')

class ConsoleMenuBoolInput : public ConsoleMenuInput {
	public:
		ConsoleMenuBoolInput(const char* command, const char* description, bool* valueTarget);
		virtual void execute(int argc, char** argv);

	protected:
		bool* valueTarget;

	private:
		bool value;
};

#endif
