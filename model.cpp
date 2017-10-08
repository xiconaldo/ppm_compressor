#include "model.h"

Model::Model(){
    for(Symbol i = 0; i < 256; i++)
        context_minus_1.insert(i);
}

void Model::updateModel(Context& context, Symbol& symbol){

    Context aux_ctx = context;
    Tree* node;
    
    while( true ){
        node = &tree;
        
        node = node->findPath(aux_ctx);

        if(!node){
            node = node->addPath(aux_ctx);
            node->addPath(EOF);
            node->addPath(symbol);
        }
        else{
            if( !node->findPath(symbol) ) node->addPath(EOF);
            node->addPath(symbol);
        }

        if( node->contexts() == 257 ) node->erasePath(EOF);

        if(aux_ctx.empty()) break;
        aux_ctx.pop_front();
    }

    if( context_minus_1.count(symbol) )
        context_minus_1.erase(symbol);

}

ProbabilitiesSet Model::getSymbolProbability(Context& context, Symbol& symbol){

    Context aux_ctx = context;
    Tree* node, aux_node;
    ProbabilitiesSet out;
    uint low, high, den;
    
    while( true ){
        node = &tree;
        
        node = node->findPath(aux_ctx);

        if(!node){
            aux_ctx.pop_front();
            continue;
        }
        
        if( aux_node = node->findPath(symbol) ){
            low = node->getOcurrencesFromPreviousSimblings(symbol);
            high = low + aux_node->ocurrences();
            den = node->contexts();
            out.push_back( {low, high, den } );
            break;
        }
        
        aux_node = node->findPath(EOF);
        low = node->getOcurrencesFromPreviousSimblings(EOF);
        high = low + aux_node->ocurrences();
        den = node->contexts();
        out.push_back( {low, high, den } );
    
        if(aux_ctx.empty()) break;
        aux_ctx.pop_front();
    }

    if( context_minus_1.count(symbol) ); // context -1
        //symbol...

}