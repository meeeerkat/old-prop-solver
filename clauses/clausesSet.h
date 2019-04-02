#ifndef __CLAUSESSET_H_INCLUDED__
#define __CLAUSESSET_H_INCLUDED__

#include <iostream>
#include <set>
#include <string>
#include "clause.h"
#include "../propTree/propTree.h"




class ClausesSet : private std::set<Clause>
{
public:
	typedef std::set<std::string> Variables;

	ClausesSet(ClausesSet const& clausesSet, bool const& removeTautologies = true);
	ClausesSet(PropTree* cnfTree);


	void saturate();

	void simplifyAssuming(Literal const& h);

	// This gives only the usefull variables if it has been saturated (variables might be simplified)
	Variables getCurrentVariables() const; 


	bool isEmpty() const;
	bool hasEmptyClause() const;

private:
	void recursivelyConstruct(PropTree* t);
	Clause recursivelyGetClause(PropTree* orTree);

	// Called during construction
	// All other operations wont allow tautologies to be added hence it's private
	void removeTautologies();

      	friend std::ostream &operator<<(std::ostream &out, ClausesSet const& c);

};

#endif
