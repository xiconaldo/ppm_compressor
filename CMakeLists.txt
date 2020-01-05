cmake_minimum_required(VERSION 3.13)

project(PPMCompressor 	VERSION 1.0
						DESCRIPTION "PPM Compressor"
						LANGUAGES CXX)

add_executable(compressor)

#Include directories and files
target_include_directories(compressor
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

include("sourcelist.cmake")

# Link directories
# Link libraries

# Compiler
target_compile_options(compressor
	PRIVATE "-Wall")

target_compile_features(compressor
	PUBLIC	cxx_std_11)