#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>

int main(){

	uint in_size, out_size;
	float RC;

	std::string s = "gow.txt";
	
	FileSymbolBuffer message{s};
	FileSymbolBuffer haha{"output.txt"};
	MemoryBitBuffer output;
	Model m{2};
	ArithmeticCompressor comp{&m};
	
	in_size = message.size();
	comp.encode(message, output);
	out_size = output.size();
	comp.decode(output, haha, in_size/8);

	RC = (float)in_size / out_size;
	std::cout << "Input  size = " << in_size << " bits" << std::endl;
	std::cout << "Output size = " << out_size << " bits" << std::endl;
	std::cout << "RC          = " << RC << " : 1" << std::endl;

	return 0;
}