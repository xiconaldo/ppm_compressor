#ifndef MODEL_H
#define MODEL_H

#include "definitions.h"
#include "tree.h"
#include "probability.h"
#include <iostream>
#include <set>

class Model{

private:
    uchar k;
    uint alphabet_size;
    Tree tree;
    std::set<Symbol> context_minus_1;
    std::unordered_set<Symbol> exc_mec;    

public:
    Model();
    void updateModel(const Context& context, const Symbol& symbol);
    ProbabilitiesSet getSymbolProbability(const Context& context, const Symbol& symbol);
    ProbabilitiesSet getSymbolProbability(int x, const Symbol& symbol);
    Symbol getSymbol(const Context& context, uint count);
    Symbol getSymbol(int x, uint count);
    uchar getK() const;
    uint getCount(const Context& context);
    uint getCount(int x);
    void clearModel();
    ProbabilityRange getSingleProbability(const Context& context, const Symbol& symbol);
    ProbabilityRange getSingleProbability(int x, const Symbol& symbol);
    void printExc();
};

#endif // MODEL_H