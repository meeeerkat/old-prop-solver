#ifndef __MODELSTREE_H_INCLUDED__
#define __MODELSTREE_H_INCLUDED__

#include <vector>
#include "../general/tree.h"
#include "../clauses/clausesSet.h"



class ModelsTree : public Tree
{
public:
	ModelsTree(ClausesSet const& c);
	ModelsTree(ClausesSet const& c, std::set<std::string> const& variables);
	virtual ~ModelsTree();

	// For base Tree class
	virtual Tree* getLeft() const;
	virtual Tree* getRight() const;
 	virtual std::string nodeToString() const;


	ModelsTree *left, *right;

private:
	// Internal constructors & helper function
	void setupModelsTree(ClausesSet const& c, ClausesSet::Variables::const_iterator varIt, ClausesSet::Variables::const_iterator const& end);
	ModelsTree(ClausesSet const& c, ClausesSet::Variables::const_iterator varIt, ClausesSet::Variables::const_iterator const& end);
	ModelsTree();

	std::string variable;
};

#endif
