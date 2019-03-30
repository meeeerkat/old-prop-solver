#ifndef __PROPTREE_H_INCLUDED__
#define __PROPTREE_H_INCLUDED__

#include <map>
#include <string>
#include <vector>


class PropTree {
public:
	enum Operator{None=100, Not=5,And=4,Or=3,Implies=2,Equivals=1};

	PropTree(Operator op = Operator::None, PropTree* left = nullptr, PropTree* right = nullptr);
	PropTree(std::string symbol, PropTree* left = nullptr, PropTree* right = nullptr);
	PropTree(PropTree* t);

	virtual ~PropTree();

	// Display
 	virtual std::string nodeToString() const;
	void display(int indent=0, int const& indentSize=4) const;

 	//virtual std::string getFormula() const;

	Operator getOperator() const;
	void setOperator(Operator op);

	std::string getSymbol() const;
	virtual void setSymbol(std::string symbol);
	bool hasPriorityOver(PropTree const& t) const;

	bool isVariable() const;
	bool isLiteral() const;

	static bool isOperatorSymbol(std::string const& s);

	PropTree *left, *right;
	std::vector<PropTree*> getChildren() const;


protected:
	Operator op;
	std::string symbol;
	
	static std::map<std::string, Operator> StringToOperators;
	static std::map<Operator, std::string> OperatorsToString;
};

#endif

