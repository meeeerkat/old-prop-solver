
#include <iomanip>
#include "clausesSet.h"



ClausesSet::ClausesSet(PropTree* cnfTree)
	: std::set<std::set<Literal>>()
{
	recursivelyConstruct(cnfTree);
}


void ClausesSet::recursivelyConstruct(PropTree* t)
{
	if(!t) return;

	if(t->getOperator() == PropTree::Operator::Or || t->isLiteral())
		insert(recursivelyGetClause(t));
	else // The recursivelyGetClause did all the way down the tree if the condition was true, else we continue to search
	{
		recursivelyConstruct(t->left);
		recursivelyConstruct(t->right);
	}
}

ClausesSet::Clause ClausesSet::recursivelyGetClause(PropTree* orTree)
{
	if(!orTree) return Clause();
	
	if(orTree->isVariable()) return Clause{Literal{orTree->getSymbol()}};
	else if(orTree->isLiteral()) return Clause{Literal{orTree->right->getSymbol(), true}};

	Clause c1 = recursivelyGetClause(orTree->left);
	Clause c2 = recursivelyGetClause(orTree->right);
	c1.insert(c2.begin(), c2.end());
	return c1;
}




void ClausesSet::saturate()
{

}

ClausesSet::Clause ClausesSet::getResultant(Clause const& a, Clause const& b)
{
	return Clause();
}


std::ostream &operator<<(std::ostream &out, ClausesSet const& c)
{
    	for (auto it = c.begin(); it != c.end(); it++) 
	{
    		for (auto it2 = (*it).begin(); it2 != (*it).end(); it2++) 
        		out << std::setw(8) << *it2 << " "; 
		out << std::endl;
	}
	return out;
}

