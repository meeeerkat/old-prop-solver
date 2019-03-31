#ifndef __CLAUSESSET_H_INCLUDED__
#define __CLAUSESSET_H_INCLUDED__

#include <iostream>
#include <set>
#include <string>
#include "clause.h"
#include "../propTree/propTree.h"




class ClausesSet : public std::set<Clause>
{
public:
	typedef std::set<std::string> Variables;

	ClausesSet(ClausesSet const& clausesSet);
	ClausesSet(PropTree* cnfTree);


	void saturate();

	void simplifyAssuming(Literal const& h);

	Variables getVariables() const;


	bool isEmpty() const;
	bool hasEmptyClause() const;

private:
	void recursivelyConstruct(PropTree* t);
	Clause recursivelyGetClause(PropTree* orTree);


      	friend std::ostream &operator<<(std::ostream &out, ClausesSet const& c);

};

#endif
