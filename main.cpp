#include <iostream>
#include "propTree/formulaParsor.h"
#include "propTree/cnfTransform.h"



int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = getPropTree(formula);

	toCNF(t);

	t->display();
	delete(t);

	return 0;
}



