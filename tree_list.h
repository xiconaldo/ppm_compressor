#ifndef TREE_LIST_H
#define TREE_LIST_H

#include "definitions.h"
#include <forward_list>
#include <unordered_set>

class TreeList{

public:
	TreeList();
    TreeList(const Symbol& symbol);
	TreeList* addPath(const Context& context);
	TreeList* addPath(const Symbol& symbol);
	TreeList* findPath(const Context& context);
	TreeList* findPath(const Symbol& symbol);
	void eraseEscape();
	void clear();

	Symbol getSymbolOnCount(uint count, const std::unordered_set<Symbol>& exc_mec) const;
	uint getOcurrencesFromPreviousSimblings(const Symbol& symbol) const;
	void getChildrenSet(std::unordered_set<Symbol>& exc_set) const;
	uint ocurrences() const;
	uint contexts() const;
	uint child_count() const;
    Symbol get_symbol() const;

private:
	Symbol symbol_;
	ushort size;
	uint num_ocurrences_ = 0;
	uint contexts_count_ = 0;
	std::forward_list<TreeList*> children;

	TreeList* addChild(const Symbol& symbol);
	TreeList* findChild(const Symbol& symbol);
};

#endif // TREE_LIST_H