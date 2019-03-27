#ifndef __FORMULAPARSOR_H_INCLUDED__
#define __FORMULAPARSOR_H_INCLUDED__

#include <string>
#include <vector>
#include "propTree.h"


// A static class so internal functions are hidden from the user
// Could have used functions declared in other functions but it's not that clean

// TO MAKE STATIC (SEARCH SYNTAX)

class FormulaParsor
{
public:
 	static PropTree* getPropTree(std::string const& formula);

	static PropTree* createNewPropTree(std::string const& op);

protected:
	static PropTree* getPropTreeRecursive(std::string const& formula, int startI, int endI);

	static void passParenthesis(std::string const& formula, int& i);
	static bool canRemoveExtremeParenthesis(std::string const& formula, int startI, int endI);
	static void cleanSubFormulaIndexs(std::string const& formula, int& startI, int& endI);

	static bool canBeVariable(std::string const& formula, int const& startI, int const& endI);
};


#endif
