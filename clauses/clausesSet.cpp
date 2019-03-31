
#include "clausesSet.h"


// Construction from CNF tree
ClausesSet::ClausesSet(PropTree* cnfTree)
	: std::set<Clause>()
{
	recursivelyConstruct(cnfTree);
}

void ClausesSet::recursivelyConstruct(PropTree* t)
{
	if(!t) return;

	if(t->getOperator() == PropTree::Operator::Or || t->isLiteral())
		insert(Clause(t));
	else // The Clause constructor went all the way down the tree if the condition was true, else we continue to search
	{
		recursivelyConstruct(t->left);
		recursivelyConstruct(t->right);
	}
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
			Clause res = Clause::getResultantOrTautology(*x, *y, isUsefull);
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


void ClausesSet::simplifyAssuming(Literal const& h)
{
	Literal const notH = h.getNegation();
	auto it = begin();
	while(it != end()) 
	{
		if(it->count(h))
		{
			erase(it);
			continue; // No it increment here
		}

		auto toRemove = it->find(notH);
		if(toRemove != it->end())
		{
			// We can modify an element in a set, we need to copy, change the copy, add it and erase the old element
			Clause copy = *it;
			copy.erase(toRemove);
			insert(copy);
			erase(it);
		}

		it++;
	}
}


std::ostream &operator<<(std::ostream &out, ClausesSet const& c)
{
    	for (auto it = c.begin(); it != c.end(); it++) 
		out << *it << std::endl;
	return out;
}

