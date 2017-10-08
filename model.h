#ifndef MODEL_H
#define MODEL_H

class Model{

private:
    uchar K;
    Tree tree;
    std::unordered_set<Symbol> context_minus_1;

public:
    Model();
    void updateModel(Context& context, Symbol& symbol);
    ProbabilitiesSet getSymbolProbability(Context& context, Symbol& symbol);
    Symbol getSymbol(Context& context, uint count);
};

#endif // MODEL_H