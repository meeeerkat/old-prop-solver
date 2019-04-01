
#include "modelsTableFactory.h"



ModelsTableFactory::ModelsTableFactory(ModelsTree* modelsTree, Variables const& variables)
	: modelsTree(modelsTree), variables(variables)
{}

ModelsTableFactory::Tab ModelsTableFactory::getTab(Criteria const& c) const
{
	return getTabRecursive(modelsTree, variables.size(), c);
}


ModelsTableFactory::Tab ModelsTableFactory::getTabRecursive(ModelsTree* t, int variablesNb, Criteria const& c) const
{
	if(!t->left && !t->right)
		return getAllPossibilities(variablesNb);

	Tab leftTab, rightTab;
	if(t->left)
		leftTab = getTabRecursive(t->left, variablesNb-1, c);
	if(t->right)
		rightTab = getTabRecursive(t->right, variablesNb-1, c);

	for(auto it=leftTab.begin(); it != leftTab.end(); it++)
		it->push_back(false);
	for(auto it=rightTab.begin(); it != rightTab.end(); it++)
		it->push_back(true);
	
	// USE THAT    leftTab.insert(rightTab.begin(), rightTab.end());
	// TEMPORARY SOLUTION UNTIL INTERNET KICKS IN
	for(auto it=rightTab.begin(); it != rightTab.end(); it++)
		leftTab.push_back(*it);

	// Reversing the vectors to have then in the right order
	/* THERE IS A STANDART FUNCTION FOR THAT, JUST NEED TO FIND IT
	for(auto it=leftTab.begin(); it != leftTab.end(); it++)
		it->reverse();
	*/

	return leftTab;
}

ModelsTableFactory::Tab ModelsTableFactory::getAllPossibilities(int depth)
{
	Tab poss{{}};

	while(depth > 0)
	{
		const int possSize = poss.size();
		// Does this reserve pos.size() more space or just sets the space ??:   pos.reserve(pos.size());
		for(int i=0; i < possSize; i++)
		{
			std::vector<bool> copy(poss[i]);
			copy.push_back(true);
			poss.push_back(copy);

			poss[i].push_back(false);
		}

		depth--;
	}

	return poss;
}


