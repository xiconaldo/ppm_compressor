#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>

int main(){

	Model m;
	//std::string s = "a";
	//std::string s = "abracadabra";
	//std::string s = "A casa de maria eh a";
	//std::string s = "aakjskajsjqwkjqwjqjwc";
	std::string s = "a c";
    MemorySymbolBuffer message{s};
	MemoryBitBuffer output;
	
	message.print();
	std::cout << std::endl;

	ArithmeticCompressor comp{&m};
	
	comp.encode(message, output);
	output.print();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	message.reset();
	comp.decode(output, message, s.size());
	message.print();
	std::cout << std::endl;

	return 0;
}