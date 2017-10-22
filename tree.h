#ifndef TREE_H
#define TREE_H

#include "definitions.h"
#include <unordered_set>

class Tree{

public:
	virtual Tree* addPath(const Context& context) = 0;
	virtual Tree* addPath(const Symbol& symbol) = 0;
	virtual Tree* findPath(const Context& context) = 0;
	virtual Tree* findPath(const Symbol& symbol) = 0;
	virtual void eraseEscape() = 0;
	virtual void clear() = 0;

	virtual Symbol getSymbolOnCount(uint count, const std::unordered_set<Symbol>& exc_mec) const = 0;
	virtual uint getOcurrencesFromPreviousSimblings(const Symbol& symbol) const = 0;
	virtual void getChildrenSet(std::unordered_set<Symbol>& exc_set) const = 0;
	virtual uint ocurrences() const = 0;
	virtual uint contexts() const = 0;
	virtual uint child_count() const = 0;

// protected:

// 	virtual Tree* addChild(const Symbol& symbol);
// 	virtual Tree* findChild(const Symbol& symbol);
};

#endif // TREE_H