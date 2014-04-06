#ifndef ConsoleMenuItemInput_h
#define ConsoleMenuItemInput_h

#include <WProgram.h>

#define INPUT_SIZE 255
extern char inputBuffer[INPUT_SIZE + 1];
extern int inputBufferIndex;
#define MAX_ARGUMENTS 10

#define INPUT_ACT_NONE    0
#define INPUT_ACT_CONFIRM 1
#define INPUT_ACT_RETRY   2
#define INPUT_ACT_RETURN  3

#define arlen(a) (sizeof(a) / sizeof(a[0]))

extern char NEW_LINE_CHAR;

class ConsoleMenuItem {
	public:
		ConsoleMenuItem(const char* command, const char* description);

		const char* command;
		const char* description;

		virtual void execute(int argc, char** argv) = 0;
	
	protected:
		uint8_t readInput();
		virtual uint8_t handleInputChar(char c);

	private:
};

#endif
