#include <iostream>
#include "propTree/formulaParsor.h"
#include "propTree/cnfTransform.h"
#include "solver/clausesSet.h"


int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = getPropTree(formula);

	toCNF(t);

	ClausesSet s = ClausesSet(t);
	std::cout << s << std::endl;

	delete(t);

	return 0;
}



