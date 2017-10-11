#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "definitions.h"
#include "model.h"
#include "memory_buffer.h"
#include "probability.h"
#include <bitset>


class ArithmeticCompressor{
private:
    Model* model;

public:
    ArithmeticCompressor(Model* model);
    void encode(SymbolBuffer& input, BitBuffer& output);
    void decode(BitBuffer& input, SymbolBuffer& output);
};

#endif // ARITHMETIC_COMPRESSOR_H 