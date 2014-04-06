#include "ConsoleListMenu.h"

#include <memory.h>
#include "ConsoleListMenuInput.h"
#include "ConsoleListMenuIntInput.h"

ConsoleListMenu* currentListMenu = NULL;

void callPrintList(int argc, char** argv) {
	if(currentListMenu != NULL) {
		void** targetsAddr = currentListMenu->targetList;
		void* target = targetsAddr[0];
		
		for(int i=0; i<*currentListMenu->targetCount; i++) {
			currentListMenu->printItem(i, target);
			target = (void*)((unsigned long)(target) + currentListMenu->targetSize);
		}
	}
}

void callAdd(int argc, char** argv) {
	if(currentListMenu != NULL) {
		void* oldTargetsAddr = *currentListMenu->targetList;
		int currentCount = *currentListMenu->targetCount;
		
		void* newAddr = malloc((currentCount + 1) * currentListMenu->targetSize);
		memcpy(newAddr, oldTargetsAddr, currentCount * currentListMenu->targetSize);
		*currentListMenu->targetList = newAddr;
		(*currentListMenu->targetCount)++;
		
		void* currentTarget = (void*)((uint8_t*)newAddr + currentListMenu->targetSize * currentCount);
		currentListMenu->editItem(currentTarget, true);
		
		if(currentCount > 0) {
			free(oldTargetsAddr);
		}
	}
}

void callEdit(int argc, char** argv) {
	if(currentListMenu != NULL) {
		if(argc < 1) {
			Serial.println("edit <id>");
			return;
		}
		
		int itemIndex = atoi(argv[0]);
		
		if(itemIndex < 0 || itemIndex >= *currentListMenu->targetCount) {
			Serial.println("Invalid id");
			return;
		}
		
		void* currentTarget = (void*)((uint8_t*)*currentListMenu->targetList + itemIndex * currentListMenu->targetSize);
		currentListMenu->editItem(currentTarget, false);
	}
}

void callDelete(int argc, char** argv) {
	if(currentListMenu != NULL) {
		if(argc < 1) {
			Serial.println("delete <id>");
			return;
		}
		
		int itemIndex = atoi(argv[0]);
		
		if(itemIndex < 0 || itemIndex >= *currentListMenu->targetCount) {
			Serial.println("Invalid id");
			return;
		}
		
		Serial.print("Delete ");
		Serial.println(itemIndex);
		
		int answer;
		do {
			Serial.print("Are you sure to delete [y/n]: ");
			while(!Serial.available()) { }
			answer = Serial.read();
			Serial.println();
		} while(answer != 'y' && answer != 'n');
		
		if(answer == 'y') {
			Serial.println("Deleting");
			
			currentListMenu->deleteItem(itemIndex);
			
		} else {
			Serial.println("Not deleting");
		}
	}
}

ConsoleListMenu::ConsoleListMenu(const char* command, const char* title, const char* description)
 : ConsoleMenu(command, title, description) {
	ConsoleMenuExecuter *cmdList = new ConsoleMenuExecuter("list", "Print current items", &callPrintList);
	ConsoleMenuExecuter *cmdAdd = new ConsoleMenuExecuter("add", "Add new item", &callAdd);
	ConsoleMenuExecuter *cmdEdit = new ConsoleMenuExecuter("edit", "Edit item", &callEdit);
	ConsoleMenuExecuter *cmdDelete = new ConsoleMenuExecuter("delete", "Remove item", &callDelete);
	menu_acts[0] = cmdList;
	menu_acts[1] = cmdAdd;
	menu_acts[2] = cmdEdit;
	menu_acts[3] = cmdDelete;
	menuItemCount = 4;
	menuItems = menu_acts;
}

void ConsoleListMenu::execute(int argc, char** argv) {
	currentListMenu = this;
	ConsoleMenu::execute(argc, argv);
}

void ConsoleListMenu::editItem(void* targetItem, bool setDefaultValue) {

	for(int i=0; i<itemSettingCount; i++) {
		ConsoleMenuItem* item = itemSettings[i];
		
		if(ConsoleListMenuInput* listInputItem = dynamic_cast<ConsoleListMenuInput*>(item)) {
			if(setDefaultValue)
				listInputItem->setDefaultValue(targetItem);
			listInputItem->setInputTarget(targetItem);
		}
		
		item->execute(0, NULL);
	}
	
}

void ConsoleListMenu::deleteItem(int itemIndex) {
	void* oldTargetsAddr = *currentListMenu->targetList;
	int currentCount = *currentListMenu->targetCount;
	
	void* newAddr = malloc((currentCount - 1) * currentListMenu->targetSize);
	memcpy(newAddr, oldTargetsAddr, itemIndex * currentListMenu->targetSize);
	memcpy((uint8_t*)newAddr + itemIndex * currentListMenu->targetSize, (uint8_t*)oldTargetsAddr + (itemIndex + 1) * currentListMenu->targetSize, (currentCount - itemIndex - 1) * currentListMenu->targetSize);
	
	*currentListMenu->targetList = newAddr;
	(*currentListMenu->targetCount)--;
	
	if(currentCount > 0) {
		free(oldTargetsAddr);
	}
}
