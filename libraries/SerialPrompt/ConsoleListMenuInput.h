#ifndef ConsoleListMenuInput_h
#define ConsoleListMenuInput_h

class ConsoleListMenuInput {
	public:
		virtual ~ConsoleListMenuInput() {}
		virtual void setDefaultValue(void* target) = 0;
		virtual void setInputTarget(void* target) = 0;
};

#endif
