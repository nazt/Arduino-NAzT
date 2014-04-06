#ifndef ConsoleListMenuIntInput_h
#define ConsoleListMenuIntInput_h

#include "ConsoleMenuIntInput.h"
#include "ConsoleListMenuInput.h"

class ConsoleListMenuIntInput : public ConsoleMenuIntInput, public ConsoleListMenuInput {
	public:
		ConsoleListMenuIntInput(const char* command, const char* description, size_t targetOffset, int minValue, int maxValue, int defaultValue);
		virtual void execute(int argc, char** argv);
		
		virtual void setDefaultValue(void* target);
		virtual void setInputTarget(void* target);

	protected:
		void* currentTarget;
		size_t targetOffset;
		int defaultValue;
};

#endif
