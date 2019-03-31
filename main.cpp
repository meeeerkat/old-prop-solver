#include <iostream>
#include "propTree/formulaParsor.h"
#include "propTree/cnfTransform.h"
#include "clauses/clausesSet.h"


int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = getPropTree(formula);
	t->display(0, 4);

	toCNF(t);
	t->display(0, 4);

	ClausesSet s = ClausesSet(t);
	s.saturate();
	std::cout << s << std::endl;

	delete(t);

	return 0;
}



