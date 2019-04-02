#ifndef __PROPTREE_H_INCLUDED__
#define __PROPTREE_H_INCLUDED__

#include <map>
#include <string>
#include <vector>
#include <set>
#include "../general/tree.h"


class PropTree : public Tree
{
public:
	enum Operator{None=100, Not=5,And=4,Or=3,Implies=2,Equivals=1};

	PropTree(Operator op = Operator::None, PropTree* left = nullptr, PropTree* right = nullptr);
	PropTree(std::string symbol, PropTree* left = nullptr, PropTree* right = nullptr);
	PropTree(PropTree* t);

	virtual ~PropTree();

	// For base Tree class
	virtual Tree* getLeft() const;
	virtual Tree* getRight() const;
 	virtual std::string nodeToString() const;

	Operator getOperator() const;
	void setOperator(Operator op);

	std::string getSymbol() const;
	virtual void setSymbol(std::string symbol);
	bool hasPriorityOver(PropTree const& t) const;

	bool isVariable() const;
	bool isLiteral() const;

	std::set<std::string> getAllVariables() const;

	static bool isOperatorSymbol(std::string const& s);

	std::vector<PropTree*> getChildren() const;

	PropTree *left, *right;


protected:
	Operator op;
	std::string symbol;
	
	static std::map<std::string, Operator> StringToOperators;
	static std::map<Operator, std::string> OperatorsToString;
};

#endif

