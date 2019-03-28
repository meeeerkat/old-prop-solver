#include <string>
#include "propTree.h"

std::map<std::string, PropTree::Operator> PropTree::StringToOperators = {
	{"not", Operator::Not},
	{"and", Operator::And},
	{"or", Operator::Or},
	{"->", Operator::Implies},
	{"<->", Operator::Equivals},
	{"", Operator::None},
};

std::map<PropTree::Operator, std::string> PropTree::OperatorsToString = {
	{Operator::Not, "not"},
	{Operator::And, "and"},
	{Operator::Or, "or"},
	{Operator::Implies, "->"},
	{Operator::Equivals, "<->"},
	{Operator::None, ""},
};



PropTree::PropTree(std::string symbol, Tree* left, Tree* right)
	: Tree(left, right)
{
	setSymbol(symbol);
}

PropTree::PropTree(Operator op, Tree* left, Tree* right)
	: Tree(left, right)
{
	setOperator(op);
}

PropTree::PropTree(PropTree* t)
	: Tree(), op(t->op), symbol(t->symbol)
{
	if(t->left) left = new PropTree(static_cast<PropTree*>(t->left));
	if(t->right) right = new PropTree(static_cast<PropTree*>(t->right));
}



bool PropTree::isOperatorSymbol(std::string const& symbol)
{
	return PropTree::StringToOperators.count(symbol) > 0;
}

std::string PropTree::getSymbol() const
{
	return symbol;
}

void PropTree::setSymbol(std::string s)
{
	symbol = s;
	if (PropTree::isOperatorSymbol(symbol))
		op = PropTree::StringToOperators[symbol];
	else
		op = Operator::None;
}

PropTree::Operator PropTree::getOperator() const
{
	return op;
}

void PropTree::setOperator(Operator newOp)
{
	op = newOp;
	if(op != Operator::None)
		symbol = PropTree::OperatorsToString[op];
}

std::string PropTree::nodeToString() const
{
	return symbol;
}

bool PropTree::hasPriorityOver(PropTree const& t) const
{
	return op > t.op;
}


bool PropTree::isVariable() const
{
	return op == Operator::None;
}

