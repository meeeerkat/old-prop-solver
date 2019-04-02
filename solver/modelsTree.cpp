#include "modelsTree.h"
#include <cassert>
#include <iostream>


ModelsTree::ModelsTree(ClausesSet const& c)
{
	// Does not gives all the variables since the clausesSet is assumed to be saturated
	Variables const variables = c.getCurrentVariables();
	setupModelsTree(c, variables.begin(), variables.end());
}

ModelsTree::ModelsTree(ClausesSet const& c, Variables const& variables)
{
	setupModelsTree(c, variables.begin(), variables.end());
}

// Internal constructors & the helper function
ModelsTree::ModelsTree(ClausesSet const& c, Variables::const_iterator varIt, Variables::const_iterator const& endIt)
{
	setupModelsTree(c, varIt, endIt);
}

ModelsTree::ModelsTree()
	: left(nullptr), right(nullptr), variable("treeEnd")
{}

void ModelsTree::setupModelsTree(ClausesSet const& c, Variables::const_iterator varIt, Variables::const_iterator const& endIt)
{
	assert(!c.hasEmptyClause() && !c.isEmpty() && "Useless to build a model tree if there are no models or if it's a tautology");

	variable = *varIt;

	ClausesSet leftCopy(c), rightCopy(c);
	leftCopy.simplifyAssuming(Literal{variable, true}); // left subtree corresponds to the negated one
	rightCopy.simplifyAssuming(Literal{variable, false});

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



