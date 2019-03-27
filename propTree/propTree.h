#ifndef __PROPTREE_H_INCLUDED__
#define __PROPTREE_H_INCLUDED__

#include <map>
#include <string>
#include "../general/tree.h"


class PropTree : public Tree {
public:
	enum Operator{None=100, Not=5,And=4,Or=3,Implies=2,Equivals=1};

	PropTree(std::string symbol = "", Tree* left = nullptr, Tree* right = nullptr);

 	//virtual std::string getFormula() const;
	virtual std::string nodeToString() const;

	virtual void setSymbol(std::string symbol);
	bool hasPriorityOver(PropTree const& t) const;

	static bool isOperatorSymbol(std::string const& s);

	void toNCF();



protected:
	std::string symbol;
	Operator op;
	

	typedef std::map<std::string, Operator> OpMap;
	static OpMap Operators;

	// toCNF helpers
	void replaceEquivalences();
	void replaceImplications();
	void simplifyNots();
	void distributeOrOnAnd();
};

#endif

