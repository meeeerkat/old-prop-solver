#ifndef __CLAUSESSET_H_INCLUDED__
#define __CLAUSESSET_H_INCLUDED__

#include <iostream>
#include <set>
#include "clause.h"
#include "../propTree/propTree.h"




class ClausesSet : public std::set<Clause>
{
public:
	ClausesSet(PropTree* cnfTree);


	void saturate();

	void simplifyAssuming(Literal const& h);


private:
	void recursivelyConstruct(PropTree* t);
	Clause recursivelyGetClause(PropTree* orTree);


      	friend std::ostream &operator<<(std::ostream &output, ClausesSet const& c);

};

#endif
