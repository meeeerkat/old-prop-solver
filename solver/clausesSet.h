#ifndef __CLAUSESSET_H_INCLUDED__
#define __CLAUSESSET_H_INCLUDED__

#include <iostream>
#include <set>
#include "literal.h"
#include "../propTree/propTree.h"



class ClausesSet : std::set<std::set<Literal>>
{
public:
	typedef std::set<Literal> Clause;

	ClausesSet(PropTree* cnfTree);


	void saturate();

	static Clause getResultantOrTautology(Clause const& a, Clause const& b, bool& isTautology);


private:
	void recursivelyConstruct(PropTree* t);
	Clause recursivelyGetClause(PropTree* orTree);


      	friend std::ostream &operator<<(std::ostream &output, ClausesSet const& c);

};

#endif
