#include <iostream>
#include "propTree/formulaParsor.h"
#include "propTree/cnfTransform.h"
#include "clauses/clausesSet.h"
#include "solver/modelsTree.h"
#include "solver/modelsTab.h"


int main()
{
	std::string formula;
	std::getline(std::cin, formula);
	PropTree* t = getPropTree(formula);

	toCNF(t);

	ClausesSet s(t);
	s.saturate();

	if(s.hasEmptyClause())
		std::cout << "INSATISFIABLE" << std::endl;
	else if(s.isEmpty())
		std::cout << "TAUTOLOGY" << std::endl;
	else
	{
		std::set<std::string> vars = t->getAllVariables();
		ModelsTree* mt = new ModelsTree(s, vars);

		ModelsTab tab = ModelsTab::createModelsTab(mt, vars);
		std::cout << tab << std::endl;
		
		delete(mt);
	}

	delete(t);

	return 0;
}



