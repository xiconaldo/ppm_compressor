#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "definitions.h"

class ArithmeticCompressor{
private:
    Model* model;
    uint K;

public:
    ArithmeticCompressor(Model& model);
    void compressMessage(Input& input, Output& output);
    void decompressMessage(Input& input, Output& output);
};

#endif // ARITHMETIC_COMPRESSOR_H 