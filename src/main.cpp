#include "tree.hpp"
#include "model.hpp"
#include "memory_buffer.hpp"
#include "file_buffer.hpp"
#include "arithmetic_compressor.hpp"
#include <iostream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]){

	std::cerr << "\n";
	if( argc < 3 ){
		std::cerr << "Too few arguments...\n\n";
		return 0;
	}

	uint in_size, out_size;
	float RC;
	uchar k;
	uchar header[5] = {0xAB, 0x58, 0x44, 0x47, 0xBB};
	double entropy;
	std::chrono::high_resolution_clock::time_point start_time, end_time;

	std::string compress = std::string{argv[1]};
	std::string input_file_name = std::string{argv[2]};
	std::string output_file_name;

	if(compress == "-c"){

		// Check for output file name existence
		output_file_name = input_file_name + ".xdg";
		if( std::ifstream{output_file_name} ){
			std::cerr << "Output file already exists.\n\n";
			exit(0);
		}

		// Get K value
		if( argc < 4 ) k = 2;
		else k = std::stoi(std::string{argv[3]});

		uint tree_mode = 0;
		if( argc > 4 && std::string{argv[4]} == "-map") tree_mode = 1;
		else if( argc > 4 && std::string{argv[4]} == "-list") tree_mode = 2;

		// Initialize objects
		FileSymbolBuffer input{input_file_name, FileUsage::readOnly};
		FileBitBuffer output{output_file_name, FileUsage::writeOnly};
		ArithmeticCompressor comp{k, tree_mode};

		// Write header information
		in_size = input.size();
		for(uint i = 0; i < 5; i++)
			output.writeBlock(header[i]);
		output.writeBlock(k);
		output.writeBlock(in_size/8);

		// Compress
		start_time = std::chrono::high_resolution_clock::now();
		comp.encode(input, output, entropy);
		end_time = std::chrono::high_resolution_clock::now();
		
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		out_size = output.size();
		RC = (float)in_size / out_size;

		// Print compression statistics
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
	else if(compress == "-d"){

		uint num_symbols;
		uchar header_check;

		// Input file name check
		uint s = input_file_name.size();
		if(s > 4 && input_file_name.substr( s-4 ) == ".xdg" )
			output_file_name = input_file_name.substr(0, s-4);
		else{
			std::cerr << "Incompatible file format. Please, input a XDG file.\n\n";
			exit(0);
		}
		
		// Output file name check
		if( argc > 3 ) output_file_name = std::string{argv[3]};
		if( std::ifstream{output_file_name} ){
			std::cerr << "Output file already exists.\n\n";
			exit(0);
		}

		uint tree_mode = 0;
		if( argc > 4 && std::string{argv[4]} == "-map") tree_mode = 1;
		else if( argc > 4 && std::string{argv[4]} == "-list") tree_mode = 2;

		// Create objects
		FileBitBuffer input{input_file_name, FileUsage::readOnly};
		FileSymbolBuffer output{output_file_name, FileUsage::writeOnly};

		// Extract header information
		for(uint i = 0; i < 5; i++){
			input.readBlock(header_check);
			if(header_check != header[i]){
				std::cerr << "Incompatible file format. Please, input a XDG file.\n\n";
				exit(0);
			}
		}
		input.readBlock(k);
		input.readBlock(num_symbols);

		ArithmeticCompressor comp{k, tree_mode};

		// Decompress
		start_time = std::chrono::high_resolution_clock::now();
		comp.decode(input, output, num_symbols);
		end_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

		// Print decompression information
		std::cerr << std::setprecision(3);
		std::cerr << "\n\nTotal time: " << elapsed.count()/1000.0f << " s" << std::endl;
	}
	std::cerr << "\n";

	return 0;
}