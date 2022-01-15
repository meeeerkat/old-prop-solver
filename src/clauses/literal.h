#ifndef __LITERAL_H_INCLUDED__
#define __LITERAL_H_INCLUDED__

#include <string>
#include <iostream>


struct Literal
{
	std::string variable;
	bool isNegated = false;

	bool isNegationOf(Literal const& l) const;
	Literal getNegation() const;

	bool operator==(Literal const& other);
	friend bool operator< (Literal const& a, Literal const& b);

	friend std::ostream &operator<<(std::ostream &out, Literal const& l);
};


#endif
