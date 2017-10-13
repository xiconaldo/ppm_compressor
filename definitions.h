#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <deque>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef ushort Symbol;
typedef std::deque<Symbol> Context;
enum {ESC = 256};
typedef unsigned char uchar;
typedef unsigned char Bit;

const uint g_FirstQuarter = 0x20000000U;
const uint g_ThirdQuarter = 0x60000000U;
const uint g_Half         = 0x40000000U;

#endif