#include "ConsoleMenuExecuter.h"

#include <stdio.h>

ConsoleMenuExecuter::ConsoleMenuExecuter(const char* command, const char* description, void (*func)(int argc, char** argv))
: 
ConsoleMenuItem(command, description), func(func) {
}

void ConsoleMenuExecuter::execute(int argc, char** argv) {
  (*func)(argc, argv);
}

