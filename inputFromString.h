#include "input.h"

class InputFromString: public Input{
public: 
	InputFromString(char *stringLine);
	InputFromString& operator>>(Symbol& s);
	bool end(void);
	~InputFromString(void);

private:
	std::string str;
};