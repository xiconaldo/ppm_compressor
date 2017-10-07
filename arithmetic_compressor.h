#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "definitions.h"

class ArithmeticCompressor{
private:
    Model* model;

public:
    ArithmeticCompressor(Model& model);
    void encode(Buffer<Symbol>& input, Buffer<uint>& output);
    void decode(Buffer<uint>& input, Buffer<Symbol>& output);
};

#endif // ARITHMETIC_COMPRESSOR_H 