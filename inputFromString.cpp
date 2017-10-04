#include "inputFromString.h"

InputFromString::InputFromString(char *stringLine){
	if(!str(StringLine)){
		std::snprintf(buffer, sizeof buffer, "[Error] Unable to read '%s'%s", stringLine, " string.");
		throw std::invalid_argument(buffer);
	} else {
		std::snprintf(buffer, sizeof buffer, "[OK] Read '%s'%s", stringLine, ".");
	}
}

InputFromString::OperatorRight(Symbol& x){
	str >> x;
}

InputFromString::~InputFromString(void){};