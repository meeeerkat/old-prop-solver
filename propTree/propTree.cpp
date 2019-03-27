#include <string>
#include "propTree.h"

PropTree::OpMap PropTree::Operators = {
	{"not", Operator::Not},
	{"and", Operator::And},
	{"or", Operator::Or},
	{"->", Operator::Implies},
	{"<->", Operator::Equivals},
}; 

/*
PropTree::PrioMap PropTree::Priorities = {
	{Operator::None, 100}, // Variables and empty PropTree need the max priority for algorithms to work
	{Operator::Not, 5},
	{Operator::And, 4},
	{Operator::Or, 3},
	{Operator::Implies, 2},
	{Operator::Equivals, 1},
}; 
*/

PropTree::PropTree(std::string symbol, Tree* left, Tree* right)
	: Tree(left, right)
{
	setSymbol(symbol);
}

bool PropTree::isOperatorSymbol(std::string const& symbol)
{
	return PropTree::Operators.count(symbol) > 0;
}

void PropTree::setSymbol(std::string s)
{
	symbol = s;
	if (PropTree::isOperatorSymbol(symbol))
		op = PropTree::Operators[symbol];
	else
		op = Operator::None;
}


std::string PropTree::nodeToString() const
{
	return symbol;
}

bool PropTree::hasPriorityOver(PropTree const& t) const
{
	return op > t.op;
}




// toCNF
void PropTree::toNCF()
{
	replaceEquivalences();
	replaceImplications();
	simplifyNots();
	distributeOrOnAnd();
}

void PropTree::replaceEquivalences()
{

}

void PropTree::replaceImplications()
{

}

void PropTree::simplifyNots()
{

}

void PropTree::distributeOrOnAnd()
{

}

