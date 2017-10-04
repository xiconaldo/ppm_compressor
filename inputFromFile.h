#include "input.h"

class InputFromFile: public Input{
public: 
	InputFromFile(const char *pathOfFile);
	OperatorRight(Symbol& x);
	EndFile(void);
	~InputFromFile(void);

private:
	std::fstream fileSource;
	char buffer[256];
};