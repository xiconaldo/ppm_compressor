#include "memory_buffer.h"
#include "file_buffer.h"
#include <iostream>

int main(){

    FileSymbolBuffer buffer{"casa.txt"};
    std::string s = "Klmnopqrst";
    Symbol ss;

    // for(char c : s){
    //     buffer << (Symbol)c;
    // }

    // for(char c : s){
    //     buffer << (Symbol)c;
    // }

    // s = "Uvwxyz";
    // for(char c : s){
    //     buffer << (Symbol)c;
    // }

    while(!buffer.eof()){
        buffer >> ss;
        std::cout << (char)ss;
    }


    return 0;

}