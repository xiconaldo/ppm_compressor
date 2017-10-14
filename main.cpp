#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>

int main(int argc, char* argv[]){

	uint in_size, out_size;
	float RC;
	double entropy;

	std::cerr << "\n";
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
		entropy = comp.encode(input, output);
		out_size = output.size();

		RC = (float)in_size / out_size;
		std::cerr << "\n\nInput info:" << std::endl;
		std::cerr << "  Size = " << in_size << " bits" << std::endl;
		std::cerr << "  Avg. length = " << 8.0f << " bits/symbol" << std::endl;
		std::cerr << "\nOutput info:" << std::endl;
		std::cerr << "  Size = " << out_size << " bits" << std::endl;
		std::cerr << "  Avg. length = " << (float)out_size/(in_size/8) << " bits/symbol" << std::endl;
		std::cerr << "\nEncode info:" << std::endl;
		std::cerr << "  Entropy = " << entropy << " bits/symbol" << std::endl;
		std::cerr << "  RC = " << RC << " : 1" << std::endl;
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
		std::cerr << "\n";
	}
	std::cerr << "\n";

	return 0;
}