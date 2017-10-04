#include "arithmetic_compressor.h"

ArithmeticCompressor::ArithmeticCompressor(Model* model){
    this->model = model;
}

void ArithmeticCompressor::compressMessage(Input& input, Output& output){

    uint low = 0x00000000U;
    uint high = 0xFFFFFFFFU;
    uint range;
    int pending_bits = 0;
    Symbol symbol;
    Context context;
    Probabilities prob;

    while( !input.eof() ){

        input >> symbol;

        Probabilities prob = model->getProbabilities(context, symbol);

        for(ProbabilityRange p : prob){
            range = high - low;
            low =  low + range * p.low_num / p.den;
            high =  low + range * p.high_num / p.den;

            while(true){
                if(high < 0x80000000U){
                    output << 0;
                    while ( pending_bits-- ) output << 1;
                    high <<= 1;
                    low <<= 1;
                    high |= 0x00000001U;
                }
                else if(low >= 0x80000000U){
                    output << 1;
                    while ( pending_bits-- ) output << 0;
                    high <<= 1;
                    low <<= 1;
                    high |= 0x00000001U;
                }
                else if ( low >= 0x40000000 && high < 0xC0000000U ){
                    pending_bits++;
                    low <<= 1;
                    low &= 0x7FFFFFFE;
                    high <<= 1;
                    high |= 0x80000001;
                }
                else{
                    break;
                }
            }
        }
        model->update(context, symbol);
        context.push_back(symbol);
        if(context.size() > K) context.pop_front();
}

void ArithmeticCompressor::decompressMessage(Input& input, Output& output){}