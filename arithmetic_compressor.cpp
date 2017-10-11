#include "arithmetic_compressor.h"

ArithmeticCompressor::ArithmeticCompressor(Model* model){
    this->model = model;
}

void ArithmeticCompressor::encode(SymbolBuffer& input, BitBuffer& output){

    uint low = 0x00000000U;
    uint high = 0xFFFFFFFFU;
    uint range;
    ulong aux;
    std::cout << sizeof(long);
    int pending_bits = 0;
    Symbol symbol;
    Context context;
    ProbabilitiesSet prob;

    while( !input.eof() ){

        input >> symbol;
        prob = model->getSymbolProbability(context, symbol);
        int siz = prob.size();
        for(ProbabilityRange p : prob){
            range = high - low;
            std::cout << "Low: " << std::bitset<32>(low) << std::endl << "High: " << std::bitset<32>(high) << std::endl;
            std::cout << "Range: " << std::bitset<32>(range) << std::endl;

            aux = (ulong)range * (ulong)p.low_num;
            aux = (aux << 32) / (ulong)p.den;
            low =  low + (uint)( aux >>= 32);

            aux = (ulong)range * (ulong)p.high_num;
            aux = (aux << 32) / (ulong)p.den;
            high =  low + (uint)( aux >>= 32);

            if(--siz == 0)
                std::cout << (char)symbol << " ";
            else
                std::cout << "ESC ";
            std::cout << "["  << p.low_num << "/" << p.den << ", " << p.high_num << "/" << p.den << ")" << std::endl;
            std::cout << "Low: " << std::bitset<32>(low) << std::endl << "High: " << std::bitset<32>(high) << std::endl;

            while(true){
                if(high < 0x80000000U){
                    output << 0;
                    while ( pending_bits > 0 ){
                        pending_bits--;
                        output << 1;
                    } 
                    high <<= 1;
                    low <<= 1;
                    high |= 0x00000001U;
                }
                else if(low >= 0x80000000U){
                    output << 1;
                    while ( pending_bits > 0 ){
                         output << 0;
                         pending_bits--;
                    }
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
        model->updateModel(context, symbol);
        context.push_back(symbol);
        if(context.size() > model->getK()) context.pop_front();
        output.print();
        std::cout << (char)symbol << " " << std::endl;
    }
}

void ArithmeticCompressor::decode(BitBuffer& input, SymbolBuffer& output){
    uint low = 0x00000000U;
    uint high = 0xFFFFFFFFU;
    uint range;
    uint value;
    Bit bit;
    uint count;
    uint aux_count;
    ulong aux;
    Symbol symbol;
    Context context;
    Context aux_context;
    ProbabilitiesSet prob;

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
                prob = model->getSymbolProbability(aux_context, symbol);
            }
            else{
                count = (value - low) * model->getCount(-1) / range;
                symbol = model->getSymbol(-1, count);
                prob = model->getSymbolProbability(-1, symbol);
            }

            auto p = prob[0];
            aux = (ulong)range * (ulong)p.low_num / (ulong)p.den;
            low =  low + (uint)( aux >>= 32);
            aux = (ulong)range * (ulong)p.high_num / (ulong)p.den;
            high =  low + (uint)( aux >>= 32);

            while(true) {
                if ( low >= 0x80000000U || high < 0x80000000U ) {
                    low <<= 1;
                    high <<= 1;
                    high |= 1;
                    input >> bit;
                    value <<= 1;
                    value += bit;
                } 
                else if ( low >= 0x40000000 && high < 0xC0000000U ) {
                    low <<= 1;
                    low &= 0x7FFFFFFF;
                    high <<= 1;
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
        model->updateModel(context, symbol);
        context.push_back(symbol);
        if(context.size() > model->getK()) context.pop_front();
    }
}