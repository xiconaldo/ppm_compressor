#include "inputFromString.h"

InputFromString::InputFromString(const string& stringLine){
	str = stringLine;
}

InputFromString::operator>>(Symbol& s){
    unsigned char tmp;
    str.read((char*)tmp, 1);
    s = tmp;
    return *this;
}

InputFromString::~InputFromString(void){};
