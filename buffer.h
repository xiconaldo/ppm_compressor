#ifndef BUFFER_H
#define BUFFER_H

#include "definitions.h"

class SymbolBuffer{

public:
    virtual void operator>>(Symbol& symbol) = 0;
    virtual void operator<<(const Symbol symbol) = 0;
    virtual bool eof() = 0;
    virtual void reset() = 0;
    virtual void print() = 0;
};

class BitBuffer{
    
    public:
        virtual void operator>>(Bit& symbol) = 0;
        virtual void operator<<(const Bit symbol) = 0;
        virtual bool eof() = 0;
        virtual void reset() = 0;
        virtual void print() = 0;
    };

#endif // BUFFER_H