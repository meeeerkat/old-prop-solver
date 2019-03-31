#ifndef __CLAUSE_H_INCLUDED__
#define __CLAUSE_H_INCLUDED__

#include <set>
#include "literal.h"
#include "../propTree/propTree.h"

class Clause : public std::set<Literal>
{
public:
	Clause();
	Clause(Clause const& c);

	Clause(PropTree* const& orCNFTree);
	void recursivelySetClause(PropTree* const orTree);

	static Clause getResultantOrTautology(Clause const& a, Clause const& b, bool& isTautology);

	bool isEmpty() const;

   	friend std::ostream &operator<<(std::ostream &out, Clause const& c);
};

#endif
