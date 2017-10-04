#include "input.h"

class InputFromString: public Input{
public: 
	InputFromString(char *stringLine);
	OperatorRight(Symbol& x);
	~InputFromString(void);

private:
	std::string str;
	char buffer[256];
};