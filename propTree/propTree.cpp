#include <string>
#include "propTree.h"


PropTree::OpMap PropTree::Priorities = {
	{"not", 5},
	{"and", 4},
	{"or", 3},
	{"->", 2},
	{"<->", 1},
}; 


PropTree::PropTree(std::string symbol, Tree* left, Tree* right)
	: Tree(left, right)
{
	setSymbol(symbol);
}

bool PropTree::isOperatorSymbol(std::string const& symbol)
{
	return PropTree::Priorities.count(symbol) > 0;
}

void PropTree::setSymbol(std::string s)
{
	symbol = s;
	if (PropTree::isOperatorSymbol(symbol))
		priority = PropTree::Priorities[symbol];
	else
		priority = 100; // variables and empty node gets max priority for easier use

}


std::string PropTree::nodeToString() const
{
	return symbol;
}

bool PropTree::hasPriorityOver(PropTree const& t) const
{
	return priority > t.priority;
}
