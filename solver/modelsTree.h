#ifndef __MODELSTREE_H_INCLUDED__
#define __MODELSTREE_H_INCLUDED__

#include "../general/tree.h"
#include "../clauses/clausesSet.h"



class ModelsTree : public Tree
{
public:
	ModelsTree(ClausesSet const& c);
	virtual ~ModelsTree();

	// For base Tree class
	virtual Tree* getLeft() const;
	virtual Tree* getRight() const;
 	virtual std::string nodeToString() const;


	ModelsTree *left, *right;

	std::string variable;
private:
	// Internal constructors & helper function
	void setupModelsTree(ClausesSet const& c, ClausesSet::Variables::iterator varIt, ClausesSet::Variables::iterator const& end);
	ModelsTree(ClausesSet const& c, ClausesSet::Variables::iterator varIt, ClausesSet::Variables::iterator const& end);
	ModelsTree();
};

#endif
