#include "formulaParsor.h"





PropTree* FormulaParsor::getPropTree(std::string const& formula)
{
	// TODO: remove following spaces doublons before starting recursivity (we are using the number of spaces in it)
	return getPropTreeRecursive(formula, 0, formula.size());
}

// For now if it has no spaces it can be a variable
bool FormulaParsor::canBeVariable(std::string const& formula, int const& startI, int const& endI)
{
	for(int i=startI; i < endI; i++)
		if(formula[i] == ' ' || formula[i] == '(' || formula[i] == ')')
			return false;

	// At the end, we have eliminated big cuts cause there are no spaces in the rest of the formula
	std::string symbol = formula.substr(startI, endI-startI);
	return !PropTree::isOperatorSymbol(symbol);
}


// Makes i pass the parenthesis
void FormulaParsor::passParenthesis(std::string const& formula, int& i)
{
	i++;
	for(int opened=1; opened > 0; i++)
	{
		if(formula[i] == '(') opened++;
		if(formula[i] == ')') opened--;
	}
}

bool FormulaParsor::canRemoveExtremeParenthesis(std::string const& formula, int startI, int endI)
{
	passParenthesis(formula, startI);
	return startI == endI+1;
}

void FormulaParsor::cleanSubFormulaIndexs(std::string const& formula, int& startI, int& endI)
{
	int subFormulaSize = endI-startI;
	endI -= 1; // Here endI is taken into the subFormula
	while(subFormulaSize > endI-startI)
	{
		subFormulaSize = endI-startI;
		// Spaces
		while(formula[startI] == ' ') startI++;
		while(formula[endI] == ' ') endI--;
		// Parenthesis
		if (formula[startI] == '(' && formula[endI] == ')' && canRemoveExtremeParenthesis(formula, startI, endI))
		{
			startI++;
			endI--;
		}

	}
	endI++; // In other functions, endI is not taken into the subFormula but it is the superior born
}



PropTree* FormulaParsor::getPropTreeRecursive(std::string const& formula, int startI, int endI)
{
	cleanSubFormulaIndexs(formula, startI, endI);

	// Unitary operators have their first cut useless (it gives an empty string)
	if(startI >= endI)
		return nullptr;

	// Simple cases
	if(canBeVariable(formula, startI, endI)) // Here everything that can be a variable is (no spaces in it)
		return new PropTree(formula.substr(startI, endI-startI));

	// Find the operator with minimum priority & cut the string following that operator to get children
	std::pair<int, int> cutIndexes = {}; // start of first cut
	PropTree* currentTree = new PropTree();
	int i = startI;
	while(i < endI)
	{
		if(formula[i] == '(')
			passParenthesis(formula, i);

		while(i < endI && formula[i] != ' ') i++;
		while(i < endI && formula[i] == ' ') i++;

		if(i >= endI)
			break;

		int oldI = i;
		while(i < endI && formula[i] != ' ' && formula[i] != '(') i++;
		const std::string op = formula.substr(oldI, i-oldI);

		PropTree* tree = new PropTree(op);
		if(currentTree->hasPriorityOver(*tree))
		{
			delete(currentTree); // This tree has not yet being recursively constructed for performances (we can trash it any moment)
			currentTree = tree;
			cutIndexes = {oldI, i}; // reset for this new operator
		}
		else
			delete(tree);

		while(i < endI && formula[i] == ' ') i++;
	}

	// Cutting formula & recursively getting children
	currentTree->left = getPropTreeRecursive(formula, startI, cutIndexes.first);
	currentTree->right = getPropTreeRecursive(formula, cutIndexes.second, endI);

	return currentTree;
}



