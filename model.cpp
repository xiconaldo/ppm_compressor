#include "model.h"

Model::Model(uchar k){
    for(Symbol i = 0; i < 256; i++)
        context_minus_1.insert(i);
    this->k = k;
}

void Model::updateModel(const Context& context, const Symbol& symbol){

    Context aux_ctx = context;
    Tree* node;
    
    while( true ){
        node = &tree;
        node = node->findPath(aux_ctx);

        if(!node){
            node = node->addPath(aux_ctx);
            node->addPath(ESC);
            node->addPath(symbol);
        }
        else{
            if( !node->findPath(symbol) ) node->addPath(ESC);
            node->addPath(symbol);
        }

        if( node->child_count() == 257 ) node->erasePath(ESC);

        if(aux_ctx.empty()) break;
        aux_ctx.pop_front();
    }

    if( context_minus_1.count(symbol) )
        context_minus_1.erase(symbol);

}

void Model::clearModel(){
    context_minus_1.clear();

    for(Symbol i = 0; i < 256; i++)
        context_minus_1.insert(i);

    tree.clear();
}

/////////////////////

ProbabilitiesSet Model::getProbabilities(const Context& context, const Symbol& symbol){

    Context aux_ctx = context;
    Tree* node, *aux_node;
    ProbabilitiesSet out;
    uint low, high, den;
    std::unordered_set<Symbol> exc_set;
    
    while( true ){
        node = &tree;
        
        node = node->findPath(aux_ctx);

        if(!node){
            if( aux_ctx.empty() ) break;
            aux_ctx.pop_front();
            continue;
        }
        
        if( aux_node = node->findPath(symbol) ){
            low = node->getOcurrencesFromPreviousSimblings(symbol);
            high = low + aux_node->ocurrences();
            den = node->contexts();

            // Exclusion mechanism
            for( auto element : exc_set )
                if(aux_node = node->findPath(element)){
                    den -= aux_node->ocurrences();
                    if(element < symbol){            
                        low -= aux_node->ocurrences();
                        high -= aux_node->ocurrences();
                    }
                }
            // --------------------

            out.push_back( {low, high, den } );
            break;
        }
        
        aux_node = node->findPath(ESC);
        if(!aux_node){
            if(aux_ctx.empty()) break;
            aux_ctx.pop_front();
            continue;
        }

        low = node->getOcurrencesFromPreviousSimblings(ESC);
        high = low + aux_node->ocurrences();
        den = node->contexts();

        // Exclusion mechanism
        for( auto element : exc_set )
            if(aux_node = node->findPath(element)){
                den -= aux_node->ocurrences();          
                low -= aux_node->ocurrences();
                high -= aux_node->ocurrences();
            }

        node->getChildrenSet(exc_set);
        // ------------------------

        out.push_back( {low, high, den } );
    
        if(aux_ctx.empty()) break;
        aux_ctx.pop_front();
    }

    if( context_minus_1.count(symbol) ){ 
        low = 0;
        for( auto k = context_minus_1.begin(); k != context_minus_1.end(); k++ ){
            if(*k == symbol) break;
            low++;
        }
        high = low + 1;
        den = context_minus_1.size();
        out.push_back( {low, high, den } );
    }

    return out;

}

ProbabilitiesSet Model::getProbabilities(const Symbol& symbol){

    ProbabilitiesSet out;
    uint low, high, den;

    if( context_minus_1.count(symbol) ){ 
        low = 0;
        for( auto k = context_minus_1.begin(); k != context_minus_1.end(); k++ ){
            if(*k == symbol) break;
            low++;
        }
        high = low + 1;
        den = context_minus_1.size();
        out.push_back( {low, high, den } );
    }

    return out;

}

ProbabilityRange Model::getSingleProbability(const Context& context, const Symbol& symbol){
    
    Tree* node, *aux_node;
    uint low, high, den;

    node = &tree;
    node = node->findPath(context);
    aux_node = node->findPath(symbol);

    low = node->getOcurrencesFromPreviousSimblings(symbol);
    high = low + aux_node->ocurrences();
    den = node->contexts();

    // Exclusion mechanism
    for( auto element : exc_mec )
        if(aux_node = node->findPath(element)){
            den -= aux_node->ocurrences();
            if(element < symbol){
                low -= aux_node->ocurrences();
                high -= aux_node->ocurrences();
            }
        }

    if(symbol == ESC)
        node->getChildrenSet(exc_mec);
    else
        exc_mec.clear();
    // ----------------------

    return ProbabilityRange{low, high, den};

}

ProbabilityRange Model::getSingleProbability(const Symbol& symbol){

    uint low, high, den;
    exc_mec.clear();

    if( context_minus_1.count(symbol) ){ 
        low = 0;
        for( auto k = context_minus_1.begin(); k != context_minus_1.end(); k++ ){
            if(*k == symbol) break;
            low++;
        }
        high = low + 1;
        den = context_minus_1.size();
        return ProbabilityRange{low, high, den };
    }

}

Symbol Model::getSymbol(const Context& context, uint count){

    Tree* node;
    
    node = &tree;
    node = node->findPath(context);

    if(node) return node->getSymbolOnCount(count, exc_mec);
    return ESC;

}

Symbol Model::getSymbol(uint count){

    uint aux = 0;
    
    for( auto k = context_minus_1.begin(); k != context_minus_1.end(); k++){
        aux++;
        if( aux > count) return *k;
    }

    return *context_minus_1.rbegin();
}

uint Model::getContextSize(const Context& context){

    Tree* node = &tree;
    Tree* aux_node;

    node = node->findPath(context);
    if(!node) return 0;
    uint value = node->contexts();

    // Exclusion mechanism
    for( auto element : exc_mec )
        if(aux_node = node->findPath(element))
            value -= aux_node->ocurrences();
    // ---------------------

    return value;

}

uint Model::getContextSize(){
    return context_minus_1.size();
}

uchar Model::getK() const{
    return k;
}