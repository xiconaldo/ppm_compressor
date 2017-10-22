#ifndef TREE_MAP_H
#define TREE_MAP_H

#include "tree.h"
#include <map>

class CompareSymbol{
public:
	bool operator()(const Symbol& s1, const Symbol& s2) const;
};

class TreeMap : public Tree{

public:
	TreeMap* addPath(const Context& context);
	TreeMap* addPath(const Symbol& symbol);
	TreeMap* findPath(const Context& context);
	TreeMap* findPath(const Symbol& symbol);
	void eraseEscape();
	void clear();

	Symbol getSymbolOnCount(uint count, const std::unordered_set<Symbol>& exc_mec) const;
	uint getOcurrencesFromPreviousSimblings(const Symbol& symbol) const;
	void getChildrenSet(std::unordered_set<Symbol>& exc_set) const;
	uint ocurrences() const;
	uint contexts() const;
	uint child_count() const;

private:
	uint num_ocurrences_ = 0;
	uint contexts_count_ = 0;
	std::map<Symbol, TreeMap*, CompareSymbol> children;

	TreeMap* addChild(const Symbol& symbol);
	TreeMap* findChild(const Symbol& symbol);
};

#endif // TREE_MAP_H