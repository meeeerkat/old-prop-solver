
#include "modelsTab.h"



ModelsTab ModelsTab::createModelsTab(ModelsTree* modelsTree, Variables const& vars, Criteria const& c)
{
	Tab tab = getTabRecursive(modelsTree, vars.size(), c);
	return ModelsTab(tab, vars);
}


ModelsTab::ModelsTab(Tab const& tab, Variables const& vars)
	:Tab(tab), variables(vars)
{}



ModelsTab::Tab ModelsTab::getTabRecursive(ModelsTree* t, int variablesNb, Criteria const& c)
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

ModelsTab::Tab ModelsTab::getAllPossibilities(int depth)
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


