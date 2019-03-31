#include "modelsTree.h"
#include <iostream>


ModelsTree::ModelsTree(ClausesSet const& c)
{
	ClausesSet::Variables const variables = c.getVariables();
	setupModelsTree(c, variables.begin(), variables.end());
}


// Internal constructors & the helper function
ModelsTree::ModelsTree(ClausesSet const& c, ClausesSet::Variables::iterator varIt,  ClausesSet::Variables::iterator const& endIt)
{
	setupModelsTree(c, varIt, endIt);
}

ModelsTree::ModelsTree()
	: left(nullptr), right(nullptr), variable("treeEnd")
{}

void ModelsTree::setupModelsTree(ClausesSet const& c, ClausesSet::Variables::iterator varIt,  ClausesSet::Variables::iterator const& endIt)
{
	variable = *varIt;

	ClausesSet leftCopy(c), rightCopy(c);
	leftCopy.simplifyAssuming(Literal{*varIt, true}); // left subtree corresponds to the negated one
	rightCopy.simplifyAssuming(Literal{*varIt, false});

	varIt++;
	if(leftCopy.isEmpty())
		left = new ModelsTree();
	else if(leftCopy.hasEmptyClause())
		left = nullptr;
	else
		left = new ModelsTree(leftCopy, varIt, endIt);

	if(rightCopy.isEmpty())
		right = new ModelsTree();
	else if(rightCopy.hasEmptyClause())
		right = nullptr;
	else
		right = new ModelsTree(rightCopy, varIt, endIt);
}



ModelsTree::~ModelsTree()
{
	delete(left);
	delete(right);
}



// For base Tree class
Tree* ModelsTree::getLeft() const {return left;}
Tree* ModelsTree::getRight() const {return right;}
std::string ModelsTree::nodeToString() const
{
	return variable;
}





