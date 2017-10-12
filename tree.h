#ifndef TREE_H
#define TREE_H

#include "definitions.h"
#include <map>
#include <unordered_set>

class CompareSymbol{
public:
	bool operator()(const Symbol& s1, const Symbol& s2) const;
};

class Tree{

public:
	Tree* addPath(const Context& context);
	Tree* addPath(const Symbol& symbol);
	Tree* addPath(const Context& context, const Symbol& symbol);
	Tree* findPath(const Context& context);
	Tree* findPath(const Symbol& symbol);
	Tree* findPath(const Context& context, const Symbol& symbol);
	void erasePath(const Symbol& symbol);
	uint getOcurrencesFromPreviousSimblings(const Symbol& symbol);
	uint ocurrences() const;
	uint contexts() const;
	uint child_count() const;
	Symbol getSymbolOnCount(uint count) const;
	void clear();
	void getChildrenSet(const Symbol& symbol, std::unordered_set<Symbol>& exc_set);

private:
	uint num_ocurrences_ = 0;
	uint contexts_count_ = 0;
	std::map<Symbol, Tree*, CompareSymbol> children;

	Tree* addChild(const Symbol& symbol);
	Tree* findChild(const Symbol& symbol);
};

#endif // TREE_H