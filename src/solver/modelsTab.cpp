
#include "modelsTab.h"
#include <iomanip>



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

    leftTab.insert(leftTab.end(), rightTab.begin(), rightTab.end());
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


// ModelsTab is built from the left to the right for performances (push_back instead or prepend) and is kept that way (perfs again)
// We print it the other way around
std::ostream &operator<<(std::ostream &out, ModelsTab const& mTab)
{
	for(auto i=mTab.variables.begin(); i != mTab.variables.end(); i++)
		out << *i << " ";
	out << std::endl;

	for(auto x=mTab.begin(); x != mTab.end(); x++)
	{
		auto i=mTab.variables.begin();
		auto y=x->end();
		while(y != x->begin())
		{
			y--;
			if(i->size() != 1)
				out << std::setw((i->size()-1)/2) << " ";
			out << *y;
			out << std::setw((i->size()+1)/2) << " ";
			i++;
		}
		out << std::endl;
	}

	return out;
}


