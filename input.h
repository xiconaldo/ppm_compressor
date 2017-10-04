#include <stdexcept>	//	std::invalid_argument()
#include <fstream>		//	std::fstream
#include <string>		// 	std::string
#include <sstream> 		//	std::stirngstream

#include "definitions.h"

class Input {
private:
	//?

public:
	virtual Input& operator>>(Symbol& s) = 0;
	virtual bool end(void) = 0;
};