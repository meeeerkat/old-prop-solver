#include <iostream>
#include "propTree/formulaParsor.h"
#include "propTree/cnfTransform.h"
#include "clauses/clausesSet.h"
#include "solver/modelsTree.h"
#include "solver/modelsTableFactory.h"


int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = getPropTree(formula);

	toCNF(t);

	ClausesSet s = ClausesSet(t);
	s.saturate();

	ModelsTree* mt = new ModelsTree(s);

	ModelsTableFactory tabFactory(mt, s.getVariables());
	ModelsTableFactory::Tab tab = tabFactory.getTab();
	//ModelsTableFactory::Tab tab = ModelsTableFactory::getAllPossibilities(5);
	
	for(auto x=tab.begin(); x != tab.end(); x++)
	{
		for(auto y=x->begin(); y != x->end(); y++)
			std::cout << *y << " ";
		std::cout << std::endl;
	}

	delete(mt);
	delete(t);

	return 0;
}



