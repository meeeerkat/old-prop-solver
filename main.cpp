#include <iostream>
#include "propTree/formulaParsor.h"
#include "propTree/cnfTransform.h"
#include "clauses/clausesSet.h"
#include "solver/modelsTree.h"


int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = getPropTree(formula);

	toCNF(t);
	t->display(0,4);

	ClausesSet s = ClausesSet(t);
	s.saturate();
	std::cout << s << std::endl;

	ModelsTree* mt = new ModelsTree(s);
	mt->display(0, 4, true);

	delete(mt);
	delete(t);

	return 0;
}



