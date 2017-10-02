#ifndef TREE_H
#define TREE_H

#include "definitions.h"
#include <map>

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
	uint ocurrences() const;
	uint contexts() const;

private:
	uint num_ocurrences_ = 1;
	uint contexts_count = 0;
	std::map<Symbol, Tree*, CompareSymbol> children;

	Tree* addChild(const Symbol& symbol);
	Tree* findChild(const Symbol& symbol);
};

#endif // TREE_H