#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>

int main(int argc, char* argv[]){

	uint in_size, out_size;
	float RC;

	if( argc < 4 ){
		std::cerr << "Too few arguments... " << std::endl;
		return 0;
	}

	std::string compress = std::string{argv[1]};
	std::string input_file_name = std::string{argv[2]};
	std::string output_file_name = std::string{argv[3]};


	if(compress == "-c"){

		uchar k;
		if( argc < 5 ) k = 2;
		else k = std::stoi(std::string{argv[4]});

		FileSymbolBuffer input{input_file_name};
		FileBitBuffer output{output_file_name};

		Model m{k};
		ArithmeticCompressor comp{&m};

		in_size = input.size();
		output.writeBlock(k);
		output.writeBlock(in_size/8);
		comp.encode(input, output);
		out_size = output.size();

		RC = (float)in_size / out_size;
		std::cout << "\nInput  size = " << in_size << " bits" << std::endl;
		std::cout << "Output size = " << out_size << " bits" << std::endl;
		std::cout << "RC          = " << RC << " : 1" << std::endl;
	}
	else{
		uchar k;
		uint num_symbols;

		FileBitBuffer input{input_file_name};
		FileSymbolBuffer output{output_file_name};

		input.readBlock(k);
		input.readBlock(num_symbols);
		Model m{k};
		ArithmeticCompressor comp{&m};

		comp.decode(input, output, num_symbols);
		std::cout << "\n";
	}

	return 0;
}