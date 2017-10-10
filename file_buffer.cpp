#include "file_buffer.h"

FileSymbolBuffer::FileSymbolBuffer(const std::string& file_name){
    source.open( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios::app);
    if(!source.is_open()) 
        source.open( file_name, std::ios_base::in | std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    seek_p = source.tellp();
    seek_g = 0;
}

FileSymbolBuffer::~FileSymbolBuffer(){
    source.close();
}

void FileSymbolBuffer::operator>>(Symbol& symbol){
    if(eof()) return;

    source.seekg(seek_g);

    uchar readed;
    source.read((char*)&readed, 1);
    symbol = readed;

    seek_g++;
}

void FileSymbolBuffer::operator<<(const Symbol symbol){

    source.seekp(seek_p);

    uchar writed = symbol;
    source.write((char*)&writed, 1);

    seek_p++;
}

bool FileSymbolBuffer::eof(){
    std::cout << seek_g << " < " << seek_p << std::endl;
    return seek_g > seek_p;
}

void FileSymbolBuffer::reset(){
    source.seekg(0);
    source.seekp(0);
}

void FileSymbolBuffer::print(){
    std::cout << source.rdbuf();
}

//

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
}

FileBitBuffer::~FileBitBuffer(){
    source.close();
}

void FileBitBuffer::operator>>(Bit& bit){
    if(eof()) return;

    source.seekg(seek_g);

    if(rd_mask == 0x80)
        source.read((char*)&rd_buffer, 1);

    bit = rd_mask & rd_buffer ? 1 : 0;

    rd_mask >>= 1;
    if(!rd_mask){
        rd_mask = 0x80;
        seek_g++;
    }
}

void FileBitBuffer::operator<<(const Bit bit){

    source.seekp(seek_p);

    if(bit) wr_buffer |= wr_mask;

    wr_mask >>= 1;
    if(!wr_mask){
        source.write((char*)&wr_buffer, 1);
        wr_mask = 0x80;
        wr_buffer = 0x00;
        seek_p++;
    }
}

bool FileBitBuffer::eof(){
    return source.eof();
}

void FileBitBuffer::reset(){
    source.seekg(0);
    source.seekp(0);

    wr_buffer = 0x00;
    rd_buffer = 0x00;
    wr_mask = 0x80;
    rd_mask = 0x80;
}

void FileBitBuffer::print(){
    std::cout << source.rdbuf();
}
