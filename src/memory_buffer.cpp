#include "memory_buffer.hpp"

// MemorySymbolBuffer

MemorySymbolBuffer::MemorySymbolBuffer(){
}

MemorySymbolBuffer::MemorySymbolBuffer(const std::string& symbols){
    for(uint i = 0; i < symbols.size(); i++)
        operator<<( (Symbol)symbols[i] );
}

void MemorySymbolBuffer::operator>>(Symbol& symbol){
    if( eof() ){
        symbol = 0U;
        return;
    }

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

uint MemorySymbolBuffer::size(){
    return source.size() * 8U;
}

void MemorySymbolBuffer::print(){
    for( uchar c : source)
        std::cout << (char)c;
}

//MemoryBitBuffer

MemoryBitBuffer::MemoryBitBuffer(){
    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
    bit_counter = 0;
}

MemoryBitBuffer::MemoryBitBuffer(const std::string& bits){
    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
    bit_counter = 0;

    for(uint i = 0; i < bits.size(); i++)
        if(bits[i] == '0')
            operator<<(0x00);
        else
            operator<<(0x01);
}

void MemoryBitBuffer::operator>>(Bit& bit){

    if(eof()){
        bit = 0;
        return;
    }

    if(rd_mask == 0x80)
        rd_buffer = source.front();

    bit = rd_mask & rd_buffer ? 0x01 : 0x00;
    
    rd_mask >>= 1;
    if(!rd_mask){
        rd_mask = 0x80;
        source.pop_front();
    }
    bit_counter--;
}

void MemoryBitBuffer::operator<<(const Bit bit){

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

void MemoryBitBuffer::writeBlock( uchar byte ){
    
    uchar bit_select = 0x80;
    
    while(bit_select != 0x00){
        if(bit_select & byte) operator<<(1);
        else operator<<(0);
        bit_select >>= 1;
    }
}

void MemoryBitBuffer::writeBlock( uint num ){
    uint bit_select = 0x80000000;
    
    while(bit_select != 0U){
        if(bit_select & num) operator<<(1);
        else operator<<(0);
        bit_select >>= 1;
    }
}

void MemoryBitBuffer::readBlock( uchar& byte ){
    
    uchar bit_select = 0x80;
    uchar bit;
    byte = 0x00;
    
    while(bit_select != 0x00){
        operator>>(bit);
        if(bit)
            byte |= bit_select;
        bit_select >>= 1;
    }
}

void MemoryBitBuffer::readBlock( uint& num ){
    uint bit_select = 0x80000000;
    uchar bit;
    num = 0x00000000;
    
    while(bit_select != 0U){
        operator>>(bit);
        if(bit)
            num |= bit_select;
        bit_select >>= 1;
    }
}

bool MemoryBitBuffer::eof(){
    return !bit_counter;
}

void MemoryBitBuffer::reset(){
    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
    bit_counter = 0;
    source.clear();
}

uint MemoryBitBuffer::size(){
    return bit_counter;
}

void MemoryBitBuffer::print(){

    if(!source.size()) return;

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