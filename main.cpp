#include <iostream>
#include "propTree/cnfTransform.h"
#include "propTree/formulaParsor.h"



int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = FormulaParsor::getPropTree(formula);

	CnfTransform::toCNF(t);

	t->display();
	delete(t);

	return 0;
}



