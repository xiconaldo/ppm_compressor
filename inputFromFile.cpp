#include "inputFromFile.h"

InputFromFile::InputFromFile(const char *pathOfFile){
	fileSource.open(pathOfFile, ios::in | ios::binary);
	char buffer[256];
	if(!fileSource.is_open()) {
		std::snprintf(buffer, sizeof buffer, "[Error] Unable to open '%s'%s", pathOfFile, " file!");
		throw std::invalid_argument(buffer);
	} else 
		std::snprintf(buffer, sizeof buffer, "[OK] Opened '%s'%s", pathOfFile, " file!");
}

InputFromFile::OperatorRight(Symbol& x){
	fileSource >> x;
}

InputFromFile::EndFile(void){
	return fileSource.eof();
}

InputFromFile::~InputFromFile(void){};