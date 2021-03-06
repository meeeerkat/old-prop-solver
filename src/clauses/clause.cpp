#include <iostream>
#include <iomanip>
#include <string>
#include "clause.h"


Clause::Clause()
	: std::set<Literal>()
{

}

Clause::Clause(Clause const& c)
	: std::set<Literal>(c)
{}

Clause::Clause(PropTree* const& orTree)
	: std::set<Literal>()
{
	recursivelySetClause(orTree);
}
void Clause::recursivelySetClause(PropTree* const orTree)
{
	if(!orTree) return;
	
	if(orTree->isVariable())
		insert(Literal{orTree->getSymbol()});
	else if(orTree->isLiteral())
		insert(Literal{orTree->right->getSymbol(), true});
	else
	{
		recursivelySetClause(orTree->left);
		recursivelySetClause(orTree->right);
	}
}

bool Clause::isTautology() const
{
	auto x = begin();
	auto y = begin();
	y++; // y is one step ahead
	while(x != end())
	{
		if(x->variable == y->variable) // No doublons so if two have the same variable they are the negation of each other
			return true;
		x++;
		y++;
	}
	return false;
}

Clause Clause::getResultantOrTautology(Clause const& a, Clause const& b, bool& isUsefull)
{
	isUsefull = false;
	bool alreadyFoundOne = false;
	auto ai = a.begin();
	auto bi = b.begin();
	Clause::iterator ar, br;
	while(ai != a.end() && bi != b.end())
	{
		while(ai != a.end() && ai->variable < bi->variable) ai++;
		while(bi != b.end() && bi->variable < ai->variable) bi++;
		if(ai->variable == bi->variable)
		{
			if(ai->isNegated != bi->isNegated)
			{
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
		
	isUsefull = true;

	Clause out;
	out.insert(a.begin(), ar);
	ar++;
	out.insert(ar, a.end());
	out.insert(b.begin(), br);
	br++;
	out.insert(br, b.end());
	return out;
}


bool Clause::isEmpty() const
{
	return size() == 0;
}



std::ostream &operator<<(std::ostream &out, Clause const& c)
{
	out << "{";
	for(auto it = c.begin(); it != c.end(); it++) 
		out << *it << ";";
       	out << "}";	
	return out;
}

