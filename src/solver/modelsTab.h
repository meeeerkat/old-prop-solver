#ifndef __MODELSTABLE_H_INCLUDED__
#define __MODELSTABLE_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "modelsTree.h"


// Class to get different types of tables (only models or only counter models, ...)
// Construction is made in a weird way that is optimized EXCEPT IN THE END, UNECESSARY COPY OF THE TAB IN THE CONSTRUCTOR
struct ModelsTab : public std::vector<std::vector<bool>>
{
public:
	enum Criteria {ModelsOnly, CounterModelsOnly, All};
	typedef std::set<std::string> Variables;
	typedef std::vector<std::vector<bool>> Tab;

	// ModelsTab are created using this static function
	static ModelsTab createModelsTab(ModelsTree* modelsTree, Variables const& vars, Criteria const& c = Criteria::All);


private:
	Variables variables;

	ModelsTab(Tab const& tab, Variables const& vars);
	static Tab getTabRecursive(ModelsTree* t, int variablesNb, Criteria const& c = Criteria::All);
	static Tab getAllPossibilities(int depth);


   	friend std::ostream &operator<<(std::ostream &out, ModelsTab const& mTab);
};

#endif

