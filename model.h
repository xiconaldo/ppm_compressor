#ifndef MODEL_H
#define MODEL_H

#include "definitions.h"
#include "tree.h"
#include "probability.h"
#include <set>

class Model{

private:
    uchar K;
    uint alphabet_size;
    Tree tree;
    std::set<Symbol> context_minus_1;

public:
    Model();
    void updateModel(const Context& context, const Symbol& symbol);
    ProbabilitiesSet getSymbolProbability(const Context& context, const Symbol& symbol);
    Symbol getSymbol(const Context& context, uint count);
};

#endif // MODEL_H