#ifndef TREE_LIST_H
#define TREE_LIST_H

#include "tree.h"
#include <forward_list>

class TreeList : public Tree{

public:
	TreeList* addPath(const Context& context);
	TreeList* addPath(const Symbol& symbol);
	TreeList* findPath(const Context& context);
	TreeList* findPath(const Symbol& symbol);
	void eraseEscape();
	void clear();

	Symbol getSymbolOnCount(uint count, const SymbolUSet& exc_mec) const;
	uint getOcurrencesFromPreviousSimblings(const Symbol& symbol) const;
	void getChildrenSet(SymbolUSet& exc_set) const;
	uint ocurrences() const;
	uint contexts() const;
	uint child_count() const;

    TreeList();
    TreeList(const Symbol& symbol);

private:
	Symbol symbol_;
	ushort size = 0;
	uint num_ocurrences_ = 0;
	uint contexts_count_ = 0;
	std::forward_list<TreeList*> children;

	TreeList* addChild(const Symbol& symbol);
	TreeList* findChild(const Symbol& symbol);
};

#endif // TREE_LIST_H