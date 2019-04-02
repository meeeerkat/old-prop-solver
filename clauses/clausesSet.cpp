
#include "clausesSet.h"


ClausesSet::ClausesSet(ClausesSet const& clausesSet, bool const& rmTautologies)
	: std::set<Clause>(clausesSet)
{
	if(rmTautologies)
		removeTautologies();
}


// Construction from CNF tree
ClausesSet::ClausesSet(PropTree* cnfTree)
	: std::set<Clause>()
{
	recursivelyConstruct(cnfTree);
	removeTautologies();
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
	if(isEmpty()) // Empty case makes an infinite loop
		return;

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
				if(res.size() == 0)
				{
					clear();
					insert(Clause());
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
	std::set<Clause> modifiedClauses;
	auto it = begin();
	while(it != end()) 
	{
		if(it->count(h) == 1)
			it = erase(it);
		else
		{
			auto toRemove = it->find(notH);
			if(toRemove != it->end())
			{
				// We can modify an element in a set, we need to copy, change the copy, add it and erase the old one
				// Here we want to pass on each elements so we put every modified element in a set to insert at the end
				Clause copy(*it);
				copy.erase(*toRemove);
				it = erase(it);
				modifiedClauses.insert(copy);
			}
			else // Only case where the iterator's pointed element is not erased, we continue with the next
				it++;
		}
	}
	// Inserting back modified clauses
	insert(modifiedClauses.begin(), modifiedClauses.end());
}


Variables ClausesSet::getCurrentVariables() const
{
	Variables out;
	for(auto x=begin(); x != end(); x++)
		for(auto y=x->begin(); y != x->end(); y++)
			out.insert(y->variable);
	return out;
}


bool ClausesSet::isEmpty() const
{
	return size() == 0;
}

bool ClausesSet::hasEmptyClause() const
{
	for(auto it=begin(); it!=end(); it++)
		if(it->isEmpty())
			return true;
	return false;
}

void ClausesSet::removeTautologies()
{
	auto it=begin();
	while(it != end())
	{
		if(it->isTautology())
			it = erase(it);
		else
			it++;
	}
}

std::ostream &operator<<(std::ostream &out, ClausesSet const& c)
{
	out << "{";
    	for (auto it = c.begin(); it != c.end(); it++) 
		out << *it << ";";
	out << "}";
	return out;
}

