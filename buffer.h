#ifndef BUFFER_H
#define BUFFER_H

#include "definitions.h"

template< class T >
class Buffer{

public:
    virtual void operator>>(T& symbol) = 0;
    virtual void operator<<(const T symbol) = 0;
    virtual bool eof() = 0;
    virtual void reset() = 0;
    virtual void print() = 0;
};

#endif // BUFFER_H