#include "tree_list.h"


TreeList::TreeList(const Symbol& symbol){
    this.symbol_ = symbol 
}

TreeList* TreeList::addPath(const Context& context){
	
	TreeList* child_node = this;
	TreeList* parent_node;

	for(Symbol s : context){
        parent_node = child_node;
		child_node = parent_node->findChild(s);
		if(!child_node) child_node = parent_node->addChild(s);
	}

	return child_node;
}

TreeList* TreeList::addPath(const Symbol& symbol){
    
    contexts_count_++;

	TreeList* node = this->findChild(symbol);
	if(!node) node = this->addChild(symbol);
    node->num_ocurrences_++;
    
	return node;
}

TreeList* TreeList::findPath(const Context& context){

	TreeList* node = this;

	for(Symbol s : context){
		node = node->findChild(s);
		if(!node) return nullptr;
	}

	return node;
}

TreeList* TreeList::findPath(const Symbol& symbol){
	return this->findChild(symbol);
}

/*
    Alterar !!!!!!!!!!!
*/
void TreeList::erasePath(const Symbol& symbol){
	
	contexts_count_ -= children[symbol]->num_ocurrences_;
	delete children[symbol];
	children.erase(symbol);
		
}

/*
    Alterarado !!!!!!!!!!!
*/
void TreeList::clear(){
	num_ocurrences_ = 0;
	contexts_count_ = 0;

	for( auto element : children ){
		delete element;
	}
	children.clear();
}

/*
    Alterar !!!!!!!!!!!
*/
Symbol TreeList::getSymbolOnCount(uint count, const std::unordered_set<Symbol>& exc_mec) const{
	
	uint aux = 0;

	for( auto k = children.begin(); k != children.end(); k++){
		if( !exc_mec.count(k->first) ) aux += k->second->ocurrences();
		if( aux > count) return k->first;
	}

	if( !children.empty() ) return children.rbegin()->first;
	return ESC;
}

/*
    Alterarado !!!!!!!!!!!
*/
uint TreeList::getOcurrencesFromPreviousSimblings(const Symbol& symbol) const{
	
	uint count = 0;
	auto k = children.begin();

	for( ; k != children.end(); k++)
        if(k->symbol_ == symbol)
            break
	  	count += k->num_ocurrences_;

	return count;
}

/*
    Alterarado !!!!!!!!!!!
*/
void TreeList::getChildrenSet(std::unordered_set<Symbol>& exc_set) const{
	for(auto it = children.begin(); it != children.end(); it++)
        if(it->symbol_ != ESC) exc_set.insert(it->symbol_);
}

/////////////////

uint TreeList::ocurrences() const{
	return num_ocurrences_;
}

uint TreeList::contexts() const{
	return contexts_count_;
}

uint TreeList::child_count() const{
	return children.size();
}

Symbol TreeList::get_symbol() const{
    return symbol_;
}

///////////////////////


TreeList* TreeList::addChild(const Symbol& symbol){
    auto index = children.begin();

    if(children.empty()) 
        children.push_front(TreeList(symbol));
        return children.front(); 

    for(auto it = children.begin(); it != children.end(); it++){
        if((*it) > symbol)
            break;
        index = it;
    }

    if(index == children.begin())
        children.push_front(TreeList(symbol));
        return children.front(); 

	return (children.insert_after(index, TreeList(symbol)));
}

TreeList* TreeList::findChild(const Symbol& symbol){
	for(auto it = children.begin(); it != children.end(); it++){
        if(it->symbol_ == symbol)
            return it;
    }

    return nullptr;
}