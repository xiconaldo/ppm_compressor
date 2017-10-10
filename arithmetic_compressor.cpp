#include "arithmetic_compressor.h"

ArithmeticCompressor::ArithmeticCompressor(Model* model){
    this->model = model;
}

void ArithmeticCompressor::encode(Input& input, Output& output){

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
            low =  low + (uint)(((ulong)range * (ulong)p.low_num / (ulong)p.den) >>= 32);
            high =  low + (uint)(((ulong)range * (ulong)p.high_num / (ulong)p.den) >>= 32);

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
        if(context.size() > model->k) context.pop_front();
}

void ArithmeticCompressor::decode(Input& input, Output& output){
    uint low = 0x00000000U;
    uint high = 0xFFFFFFFFU;
    uint range;
    uint value;
    uint bit;
    uint count;
    uint aux_count;
    Symbol symbol;
    Context context;
    Context aux_context;
    Probabilities prob;

    for ( uint i = 0 ; i < 32 ; i++ ) {
        input >> bit;
        value <<= 1;
        value += bit;
    }

    while(true) {
        aux_context = context;

        while(true){
            if( (aux_count = model->getCount(aux_context)) || aux_context.empty() ) break;
            aux_context.pop_front();
        }

        while(true){
            range = high - low;

            if( aux_count ){
                count = (value - low) * aux_count / range;
                symbol = model->getSymbol(aux_context, count);
                prob = model->getProbabilities(aux_context, symbol);
            }
            else{
                count = (value - low) * model->getCount(-1) / range;
                symbol = model->getSymbol(-1, count);
                prob = model->getProbabilities(-1, symbol);
            }

            p = prob[0];
            low =  low + (uint)(((ulong)range * (ulong)p.low_num / (ulong)p.den) >>= 32);
            high =  low + (uint)(((ulong)range * (ulong)p.high_num / (ulong)p.den) >>= 32);

            while(true) {
                if ( low >= 0x80000000U || high < 0x80000000U ) {
                    low <<= 1;
                    high << = 1;
                    high |= 1;
                    input >> bit;
                    value <<= 1;
                    value += bit;
                } 
                else if ( low >= 0x40000000 && high < 0xC0000000U ) {
                    low << = 1;
                    low &= 0x7FFFFFFF;
                    high << = 1;
                    high |= 0x80000001;
                    input >> bit;
                    value <<= 1;
                    value += bit;
                }
                else{
                    break;
                }
            }

            if(symbol > 255)
                aux_context.push_back(symbol);
            else
                break;
        }
        
        output << symbol;
        model->update(context, symbol);
        context.push_back(symbol);
        if(context.size() > model->k) context.pop_front();
    }
}