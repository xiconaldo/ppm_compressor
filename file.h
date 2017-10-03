#ifndef __FILE_H
#define __FILE_H

#include <map>				// 	std::map
#include <iostream>			//	std::clog
#include <fstream>			//	std::fstream
#include <string.h>			//	strcmp()
#include <stdexcept>		//	std::invalid_argument()
#include <sys/stat.h>		//	stat()
#include <sys/types.h>		//	struct

class File {
private:
	std::fstream fileSource;
	std::fstream fileTarget;

	int sizeAlpha;
	std::string * entireFile;

	void Encode(int k);
	void Decode(void);

	void LoadFile(void);
	
public:
	File(const char *path, const char *opt);
	~File(void);

	void Compress(int k);
	void Extract();
};

#endif