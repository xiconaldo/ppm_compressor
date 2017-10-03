#include "file.h"

File::File(const char *path, const char *opt) {
	struct stat sb;
	stat(path, &sb);

	// is path a regular file?
	if(!S_ISREG(sb.st_mode)) {
		char buffer[256];
		std::snprintf(buffer, sizeof buffer, "[Error] '%s'%s", path, " is not a regular file!");
		throw std::invalid_argument(buffer);
	} else {
		std::snprintf(buffer, sizeof buffer, "[OK] '%s'%s", path, " is a regular file!");
	}
	fileSource.open(path, ios::in | ios::binary);

	// is file open properly?
	if(!fileSource.is_open()) {
		char buffer[256];
		std::snprintf(buffer, sizeof buffer, "[Error] Unable to open '%s'%s", path, " file!");
		throw std::invalid_argument(buffer);
	} else {
		std::snprintf(buffer, sizeof buffer, "[OK] Opened '%s'%s", path, " file!");
	}
	std::string pathOutput(path);

	// Type of action - Compress or Extract
	if(strcmp(opt, "C") == 0) {
		pathOutput += ".ppmc";
		fileTarget.open(pathOutput.c_str(), std::ios::out | std::ios::binary);
	} else {
		fileTarget.open(pathOutput.substr(0, pathOutput.find_last_of(".")).c_str(), std::ios::out | std::ios::binary);
	}

	// is target file open properly?
	if(!fileTarget.is_open()) {
		char buffer[256];
		std::snprintf(buffer, sizeof buffer, "[Error] Unable to open '%s'%s", pathOutput.c_str(), " file!");
		throw std::invalid_argument(buffer);
	} else {
		std::snprintf(buffer, sizeof buffer, "[OK] Opened '%s'%s", pathOutput.c_str(), " file!");
	}
	
	//ArithmeticCoderC goes here?
}

File::~File(void){}

void File::LoadFile(void)
{
	// file size
	fileSource.seekg(0, std::ios::end);
	std::size_t size = fileSource.tellg();
	fileSource.seekg(0, std::ios::beg);

	// reads all file
	std::vector<char> vectorFile (size/sizeof(char));
	fileSource.read((char *) &vectorFile[0], size);

	// Count the sizeAlpha
	std::map<char, int> frequencies;

	for(unsigned int i = 0 ; i < size; i++)
	{
		frequencies[vectorFile[i]] = 1;
	}
	sizeAlpha = frequencies.size();

	// Converts std::vector<char> to std::string
	entireFile = new std::string(vectorFile.begin(), vectorFile.end());
}

void File::Encode(int k) {
	std::clog << "# Encoding..." << std::endl;
}

void File::Decode(void) {
	std::clog << "# Deconding..." << std::endl;
}

void File::Compress(int k) {
	std::clog << "# Compressing..." << std::endl;
}

void File::Extract(void) {
	std::clog << "# Extracting..." << std::endl;
}