#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>
#include <chrono>

int main(int argc, char* argv[]){

	uint in_size, out_size;
	float RC;
	double entropy;
	std::chrono::high_resolution_clock::time_point start_time, end_time;

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

		start_time = std::chrono::high_resolution_clock::now();
		entropy = comp.encode(input, output);
		end_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

		out_size = output.size();
		

		RC = (float)in_size / out_size;
		std::cerr << std::setprecision(3);
		std::cerr << "\n\nTotal time: " << elapsed.count()/1000.0f << " s" << std::endl;
		std::cerr << "\nInput info:" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Size: " << in_size/1024 << " kb" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Avg. length: " << 8.0f << " bits/symbol" << std::endl;
		std::cerr << "\nOutput info:" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Size: " << out_size/1024 << " kb" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Avg. length: " << (float)out_size/(in_size/8) << " bits/symbol" << std::endl;
		std::cerr << "\nEncode info:" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Entropy: " << entropy << " bits/symbol" << std::endl;
		std::cerr << std::setw(15) << std::left << "  RC: " << RC << " : 1" << std::endl;
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

		start_time = std::chrono::high_resolution_clock::now();
		comp.decode(input, output, num_symbols);
		end_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

		std::cerr << std::setprecision(3);
		std::cerr << "\n\nTotal time: " << elapsed.count()/1000.0f << " s" << std::endl;
	}
	std::cerr << "\n";

	return 0;
}