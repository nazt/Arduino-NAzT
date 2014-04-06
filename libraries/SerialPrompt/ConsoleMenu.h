#ifndef ConsoleMenu_h
#define ConsoleMenu_h

#include "ConsoleMenuItem.h"

// For easy including
#include "ConsoleMenuIntInput.h"
#include "ConsoleMenuBoolInput.h"
#include "ConsoleMenuExecuter.h"

class ConsoleMenu : public ConsoleMenuItem {
	public:
		ConsoleMenu(const char* command, const char* title, const char* description);

		void listCommands(char* prefix);

		const char* title;

		int menuItemCount;
		ConsoleMenuItem** menuItems;

		void executeMenuItem(ConsoleMenuItem* menuItem);

		virtual void execute(int argc, char** argv);
		virtual uint8_t handleInputChar(char c);

	private:
		bool handleInputBuffer();
};

#endif
