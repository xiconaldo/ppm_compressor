#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <deque>
#include <unordered_set>
#include <set>

typedef unsigned int uint;
typedef unsigned short ushort;
typedef ushort Symbol;
typedef std::deque<Symbol> Context;
typedef std::unordered_set<Symbol> SymbolUSet;
typedef std::set<Symbol> SymbolSet;
enum {ESC = 256};
typedef unsigned char uchar;
typedef unsigned char Bit;

#endif