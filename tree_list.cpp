#include "tree_list.h"

// OK
TreeList::TreeList(){
	this->symbol_ = 0;
}

TreeList::TreeList(const Symbol& symbol){
	this->symbol_ = symbol;
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
void TreeList::eraseEscape(){

	size--;
	for( auto k : children)
		if( k->symbol_ == ESC){
			contexts_count_ -= k->num_ocurrences_;
			delete k;
			break;
		}

	children.remove(nullptr);
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

	for( auto k : children){
		if( !exc_mec.count(k->symbol_) ) aux += k->ocurrences();
		if( aux > count) return k->symbol_;
	}

	//if( !children.empty() ) return children.rbegin()->first;
	return ESC;
}

/*
	Alterarado !!!!!!!!!!!
*/
uint TreeList::getOcurrencesFromPreviousSimblings(const Symbol& symbol) const{
	
	uint count = 0;

	for( auto k : children){
		if(k->symbol_ == symbol) break;
		count += k->num_ocurrences_;
	}

	return count;
}

/*
	Alterarado !!!!!!!!!!!
*/
void TreeList::getChildrenSet(std::unordered_set<Symbol>& exc_set) const{
	for(auto tree : children)
		if(tree->symbol_ != ESC)
			exc_set.insert(tree->symbol_);
}

/////////////////

uint TreeList::ocurrences() const{
	return num_ocurrences_;
}

uint TreeList::contexts() const{
	return contexts_count_;
}

uint TreeList::child_count() const{
	return (uint)size;
}

Symbol TreeList::get_symbol() const{
	return symbol_;
}

///////////////////////


TreeList* TreeList::addChild(const Symbol& symbol){
	
	auto new_tree_pointer = new TreeList{symbol};

	auto it = children.before_begin();
	auto prev = it;

	while( ++it != children.end() ){
		if( (*it)->symbol_ > symbol)
			break;
		prev = it;
	}

	children.insert_after(prev, new_tree_pointer );
	size++;

	return new_tree_pointer;
		
}

TreeList* TreeList::findChild(const Symbol& symbol){
	for(auto tree : children){
		if(tree->symbol_ == symbol)
			return tree;
	}

	return nullptr;
}