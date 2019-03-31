
#include <iomanip>
#include "clausesSet.h"


// Construction from CNF tree
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




// Saturation
void ClausesSet::saturate()
{
	auto endX = end();
	endX--; // Ending is not end() or infinite loop
	for(auto x=begin(); x != endX; x++)
	{
		auto y=x;
		y++;
		while(y != end())
		{
			bool isUsefull;
			Clause res = getResultantOrTautology(*x, *y, isUsefull);
			if(isUsefull)
			{
				if(res.empty())
				{
					clear();
					insert(Clause{});
					return;
				}
				insert(res);
			}
			y++;
		}
	}
}

ClausesSet::Clause ClausesSet::getResultantOrTautology(Clause const& a, Clause const& b, bool& isUsefull)
{
	isUsefull = false;
	bool alreadyFoundOne = false;
	auto ai = a.begin();
	auto bi = b.begin();
	Clause::iterator ar, br;
	while(ai != a.end() && bi != b.end())
	{
		while(ai != a.end() && (*ai).variable < (*bi).variable) ai++;
		while(bi != b.end() && (*bi).variable < (*ai).variable) bi++;
		if((*ai).variable == (*bi).variable)
		{
			if((*ai).isNegated != (*bi).isNegated)
			{
				isUsefull = true;
				if(alreadyFoundOne) // There are at least 2 variables that could be simplified but each cases gives a tautology
					return Clause();
				alreadyFoundOne = true;
				ar = ai;
				br = bi;
			}
			ai++;
			bi++;
		}
	}

	if(!alreadyFoundOne)
		return Clause();
		

	Clause out;
	out.insert(a.begin(), ar);
	ar++;
	out.insert(ar, a.end());
	out.insert(b.begin(), br);
	br++;
	out.insert(br, b.end());
	return out;
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

