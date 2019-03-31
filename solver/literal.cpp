#include "literal.h"



bool Literal::isNegationOf(Literal const& l) const
{
	return variable == l.variable && isNegated == !l.isNegated;
}

bool Literal::operator==(Literal const& l)
{
	return variable == l.variable && isNegated == l.isNegated;
}


bool operator<(Literal const& a, Literal const& b)
{
	return a.variable < b.variable || (a.variable == b.variable && a.isNegated < b.isNegated);
}


std::ostream &operator<<(std::ostream &out, Literal const& l)
{
	if(l.isNegated)
		out << "not ";
	out << l.variable;
	return out;
}

