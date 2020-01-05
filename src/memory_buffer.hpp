#ifndef MEMORY_BUFFER_H
#define MEMORY_BUFFER_H

#include "buffer.hpp"
#include <iostream>

class MemorySymbolBuffer : public SymbolBuffer{
    
private:
    std::deque<Symbol> source;

public:
    MemorySymbolBuffer();
    MemorySymbolBuffer(const std::string& symbols);
    void operator>>(Symbol& symbol);
    void operator<<(const Symbol symbol);
    bool eof();
    void reset();
    uint size();
    void print();
};

class MemoryBitBuffer : public BitBuffer{
    
private:
    std::deque<Bit> source;
    uchar wr_buffer;
    uchar rd_buffer;
    uchar wr_mask;
    uchar rd_mask;
    uint bit_counter;

public:
    MemoryBitBuffer();
    MemoryBitBuffer(const std::string& bits);
    void operator>>(Bit& bit);
    void operator<<(const Bit bit);
    void writeBlock( uchar byte );
    void writeBlock( uint num );
    void readBlock( uchar& byte );
    void readBlock( uint& num );
    bool eof();
    void reset();
    uint size();
    void print();
};

#endif // MEMORY_BUFFER_H