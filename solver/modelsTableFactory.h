#ifndef __MODELSTABLE_H_INCLUDED__
#define __MODELSTABLE_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "modelsTree.h"


// Class to get different types of tables (only models or only counter models, ...)
class ModelsTableFactory
{
public:
	enum Criteria {ModelsOnly, CounterModelsOnly, All};
	typedef std::set<std::string> Variables;
	typedef std::vector<std::vector<bool>> Tab;

	ModelsTableFactory(ModelsTree* modelsTree, Variables const& variables);

	Tab getTab(Criteria const& c = Criteria::All) const;
	static Tab getAllPossibilities(int depth);

private:
	ModelsTree* modelsTree;
	Variables variables;

	Tab getTabRecursive(ModelsTree* t, int variablesNb, Criteria const& c = Criteria::All) const;
};

#endif

