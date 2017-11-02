#include "file_buffer.h"

// FileSymbolBuffer

FileSymbolBuffer::FileSymbolBuffer(const std::string& file_name){
    source.open( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios::app);
    if(!source.is_open()) 
        source.open( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    source.seekg (0, source.end);
    seek_p = source.tellg();
    source.seekg (0, source.beg);
    seek_g = source.tellg();
}

FileSymbolBuffer::~FileSymbolBuffer(){
    source.close();
}

void FileSymbolBuffer::operator>>(Symbol& symbol){
    if(eof()) return;

    uchar readed;
    source.seekg(seek_g, source.beg);
    source.read((char*)&readed, 1);
    symbol = readed;
    seek_g++;
}

void FileSymbolBuffer::operator<<(const Symbol symbol){

    uchar writed = symbol;
    source.seekp(seek_p, source.beg);
    source.write((char*)&writed, 1);
    seek_p++;
}

bool FileSymbolBuffer::eof(){
    return seek_g >= seek_p;
}

void FileSymbolBuffer::reset(){
    source.seekg(0, source.beg);
    source.seekp(0, source.beg);
}

uint FileSymbolBuffer::size(){
    return (seek_p-seek_g)* 8U;
}

void FileSymbolBuffer::print(){
    std::cout << source.rdbuf();
}

// FileBitBuffer

FileBitBuffer::FileBitBuffer(const std::string& file_name){

    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
    seek_g = 0;
    seek_p = 0;

    source.open( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    if(!source.is_open()) 
        source.open( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    source.seekg (0, source.end);
    seek_p = source.tellg();
    source.seekg (0, source.beg);
    seek_g = source.tellg();
}

FileBitBuffer::~FileBitBuffer(){

    while( wr_mask != 0x80)
        operator<<(0);

    source.close();
}

void FileBitBuffer::operator>>(Bit& bit){
    if(eof()){
        bit = 0;
        return;
    }

    source.seekg(seek_g, source.beg);

    if(rd_mask == 0x80)
        source.read((char*)&rd_buffer, 1);

    bit = (rd_mask & rd_buffer) ? 1 : 0;

    rd_mask >>= 1;
    if(!rd_mask){
        rd_mask = 0x80;
        seek_g++;
    }
}

void FileBitBuffer::operator<<(const Bit bit){

    source.seekp(seek_p, source.beg);

    if(bit) wr_buffer |= wr_mask;

    wr_mask >>= 1;
    if(!wr_mask){
        source.write((char*)&wr_buffer, 1);
        wr_mask = 0x80;
        wr_buffer = 0x00;
        seek_p++;
    }
}

void FileBitBuffer::writeBlock( uchar byte ){
    
    uchar bit_select = 0x80;
    
    while(bit_select != 0x00){
        if(bit_select & byte) operator<<(1);
        else operator<<(0);
        bit_select >>= 1;
    }
}

void FileBitBuffer::writeBlock( uint num ){
    uint bit_select = 0x80000000;
    
    while(bit_select != 0x00000000){
        if(bit_select & num) operator<<(1);
        else operator<<(0);
        bit_select >>= 1;
    }
}

void FileBitBuffer::readBlock( uchar& byte ){
    
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

void FileBitBuffer::readBlock( uint& num ){
    uint bit_select = 0x80000000;
    uchar bit;
    num = 0x00000000;
    
    while(bit_select != 0x00000000){
        operator>>(bit);
        if(bit)
            num |= bit_select;
        bit_select >>= 1;
    }
}

bool FileBitBuffer::eof(){
    return ((seek_g == seek_p) && (rd_mask <= wr_mask)) || (seek_g > seek_p);
}

void FileBitBuffer::reset(){
    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
    source.seekg(0, source.beg);
    source.seekp(0, source.beg);
}

uint FileBitBuffer::size(){
    return (seek_p-seek_g)*8U;
}

void FileBitBuffer::print(){
    std::cout << source.rdbuf();
}
