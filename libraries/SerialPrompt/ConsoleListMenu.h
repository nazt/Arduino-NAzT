#ifndef ConsoleListMenu_h
#define ConsoleListMenu_h

#include "ConsoleMenu.h"
#include "ConsoleMenuExecuter.h"

#define container_of(ptr, type, member) ({            \
 const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
 (type *)( (char *)__mptr - offsetof(type,member) );})

class ConsoleListMenu : public ConsoleMenu {
	public:
		ConsoleListMenu(const char* command, const char* title, const char* description);
		virtual void execute(int argc, char** argv);
		
		void editItem(void* item, bool setDefaultValue);
		void deleteItem(int itemIndex);

		unsigned int targetSize;
		void** targetList;
		int* targetCount;
		
		int itemSettingCount;
		ConsoleMenuItem** itemSettings;

		void (*printItem)(int i, void* target);

	private:
		ConsoleMenuItem *menu_acts[4];
};

#endif
