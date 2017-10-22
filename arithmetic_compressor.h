#ifndef ARITHMETIC_COMPRESSOR_H
#define ARITHMETIC_COMPRESSOR_H

#include "definitions.h"
#include "model.h"
#include "memory_buffer.h"
#include "probability.h"
#include <bitset>
#include <iomanip>
#include <cmath>


class ArithmeticCompressor{
private:
    Model model;
    static const uint ONE_QUARTER       = 0x20000000U;
    static const uint THREE_QUARTERS    = 0x60000000U;
    static const uint ONE_HALF          = 0x40000000U;

public:
    ArithmeticCompressor(uchar k, uint tree_mode);
    void encode(SymbolBuffer& input, BitBuffer& output, double& entropy, bool clear_model = true);
    void decode(BitBuffer& input, SymbolBuffer& output, uint size, bool clear_model = true);
};

#endif // ARITHMETIC_COMPRESSOR_H 