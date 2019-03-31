#include <string>
#include <iostream>
#include <iomanip>
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



PropTree::PropTree(std::string symbol, PropTree* left, PropTree* right)
	: left(left), right(right)
{
	setSymbol(symbol);
}

PropTree::PropTree(Operator op, PropTree* left, PropTree* right)
	: left(left), right(right)
{
	setOperator(op);
}

PropTree::PropTree(PropTree* t)
	: op(t->op), symbol(t->symbol)
{
	if(t->left) left = new PropTree(t->left);
	if(t->right) right = new PropTree(t->right);
}

PropTree::~PropTree()
{
	delete(left);
	delete(right);
}


// For base Tree class
Tree* PropTree::getLeft() const {return left;}
Tree* PropTree::getRight() const {return right;}
std::string PropTree::nodeToString() const
{
	return symbol;
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


bool PropTree::hasPriorityOver(PropTree const& t) const
{
	return op > t.op;
}


bool PropTree::isVariable() const
{
	return op == Operator::None;
}

bool PropTree::isLiteral() const
{
	return isVariable() || (op == Operator::Not && right->isVariable());
}

std::vector<PropTree*> PropTree::getChildren() const
{
	return std::vector<PropTree*>{left, right};
}

