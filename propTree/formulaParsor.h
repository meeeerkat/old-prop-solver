#ifndef __FORMULAPARSOR_H_INCLUDED__
#define __FORMULAPARSOR_H_INCLUDED__

#include <string>
#include <vector>
#include "propTree.h"


PropTree* getPropTree(std::string const& formula);

PropTree* createNewPropTree(std::string const& op);




PropTree* getPropTreeRecursive(std::string const& formula, int startI, int endI);

void passParenthesis(std::string const& formula, int& i);
bool canRemoveExtremeParenthesis(std::string const& formula, int startI, int endI);
void cleanSubFormulaIndexs(std::string const& formula, int& startI, int& endI);

bool canBeVariable(std::string const& formula, int const& startI, int const& endI);

std::string getWord(std::string const& formula, int& i, int const& endI);


#endif
