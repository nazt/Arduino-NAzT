#ifndef ConsoleMenuExecuter_h
#define ConsoleMenuExecuter_h

#include "ConsoleMenuItem.h"

class ConsoleMenuExecuter : public ConsoleMenuItem {
	public:
		ConsoleMenuExecuter(const char* command, const char* description, void (*func)(int argc, char** argv));

		void (*func)(int argc, char** argv);

		virtual void execute(int argc, char** argv);

	private:
};

#endif
