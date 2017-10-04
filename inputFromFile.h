#include "input.h"

class InputFromFile: public Input{
public: 
	InputFromFile(const string& pathOfFile);
	InputFromFile& operator>>(Symbol& s);
	bool end(void);
	~InputFromFile(void);

private:
	std::fstream fileSource;
};