#include "inputFromFile.h"
 
InputFromFile::InputFromFile(const string& pathOfFile){
    std::stringstream buffer;
 
    fileSource.open(pathOfFile, ios::in | ios::binary);
    if(!fileSource.is_open()) {
        buffer << "[Error] Unable to read " << pathOfFile << "string";
        throw std::invalid_argument(buffer);
    }
}

InputFromFile::operator>>(Symbol& s){
    unsigned char tmp;
    fileSource.read((char*)tmp, 1);
    s = tmp;
    return *this;
}
 
InputFromFile::end(void){
    return fileSource.eof();
}
 
InputFromFile::~InputFromFile(void){
    fileSource.close();
};