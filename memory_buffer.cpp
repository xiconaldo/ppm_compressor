#include "memory_buffer.h"

// MemorySymbolBuffer definitions

MemorySymbolBuffer::MemorySymbolBuffer(){
}

MemorySymbolBuffer::MemorySymbolBuffer(const std::string& symbols){
    for(uint i = 0; i < symbols.size(); i++)
        operator<<( (Symbol)symbols[i] );
}

void MemorySymbolBuffer::operator>>(Symbol& symbol){
    if( eof() ) return;

    symbol = source.front();
    source.pop_front();
}

void MemorySymbolBuffer::operator<<(const Symbol symbol){
    source.push_back(symbol);
}

bool MemorySymbolBuffer::eof(){
    return !source.size();
}

void MemorySymbolBuffer::reset(){
    source.clear();
}

void MemorySymbolBuffer::print(){
    
    for( uchar c : source){
        std::cout << (char)c;
    }
}


//MemoryBitBuffer definitions

MemoryBitBuffer::MemoryBitBuffer(){
    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
}

MemoryBitBuffer::MemoryBitBuffer(const std::string& bits){
    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
    bit_counter = 0;

    for(uint i = 0; i < bits.size(); i++)
        if(bits[i] == '0')
            operator<<(0);
        else
            operator<<(1);
}

void MemoryBitBuffer::operator>>(uint& bit){

    if(eof()) return;

    if(rd_mask == 0x80)
        rd_buffer = source.front();

    bit = rd_mask & rd_buffer ? 1 : 0;
    
    rd_mask >>= 1;
    if(!rd_mask){
        rd_mask = 0x80;
        source.pop_front();
    }
    bit_counter--;
}

void MemoryBitBuffer::operator<<(const uint bit){

    if(wr_mask == 0x80){
        wr_buffer = 0x00;
        source.push_back(wr_buffer);
    }

    if(bit) wr_buffer |= wr_mask;
    source.back() = wr_buffer;

    wr_mask >>= 1;
    if(!wr_mask) wr_mask = 0x80;

    bit_counter++;
}

bool MemoryBitBuffer::eof(){
    return !bit_counter;
}

void MemoryBitBuffer::reset(){
    source.clear();
}

void MemoryBitBuffer::print(){

    uint start = 0;
    uint end = source.size() - 1;
    uchar aux_mask = rd_mask;
    uint bits_remaining = bit_counter;

    for( uint i = start; i <= end; i++){

        while( aux_mask != 0 && bits_remaining > 0){
            std::cout << ( (source[i] & aux_mask) ? 1 : 0);
            bits_remaining--;
            aux_mask >>= 1;
        }

        aux_mask = 0x80;

    }

}