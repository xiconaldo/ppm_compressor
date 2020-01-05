#ifndef TREE_H
#define TREE_H

#include "definitions.hpp"
#include <unordered_set>

class Tree{

public:

	virtual ~Tree() = 0;

	virtual Tree* addPath(const Context& context) = 0;
	virtual Tree* addPath(const Symbol& symbol) = 0;
	virtual Tree* findPath(const Context& context) = 0;
	virtual Tree* findPath(const Symbol& symbol) = 0;
	virtual void eraseEscape() = 0;
	virtual void clear() = 0;

	virtual Symbol getSymbolOnCount(uint count, const SymbolUSet& exc_mec) const = 0;
	virtual uint getOcurrencesFromPreviousSimblings(const Symbol& symbol) const = 0;
	virtual void getChildrenSet(SymbolUSet& exc_set) const = 0;
	virtual uint ocurrences() const = 0;
	virtual uint contexts() const = 0;
	virtual uint child_count() const = 0;
};

#endif // TREE_H