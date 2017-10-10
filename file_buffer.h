#ifndef FILE_BUFFER_H
#define FILE_BUFFER_H

#include "buffer.h"
#include <fstream>
#include <iostream>
#include <ios>

class FileSymbolBuffer : public Buffer<Symbol>{
    
private:
    std::fstream source;
    uint seek_g;
    uint seek_p;

public:
    FileSymbolBuffer(const std::string& file_name);
    ~FileSymbolBuffer();
    void operator>>(Symbol& symbol);
    void operator<<(const Symbol symbol);
    bool eof();
    void reset();
    void print();
};

class FileBitBuffer : public Buffer<Bit>{
    
private:
    std::fstream source;
    uchar wr_buffer;
    uchar rd_buffer;
    uchar wr_mask;
    uchar rd_mask;
    uint bit_counter;
    uint seek_g;
    uint seek_p;

public:
    FileBitBuffer(const std::string& file_name);
    ~FileBitBuffer();
    void operator>>(Bit& bit);
    void operator<<(const Bit bit);
    bool eof();
    void reset();
    void print();
};

#endif // FILE_BUFFER_H