#ifndef __PROPTREE_H_INCLUDED__
#define __PROPTREE_H_INCLUDED__

#include <map>
#include <string>
#include "../general/tree.h"


class PropTree : public Tree {
public:
	PropTree(std::string symbol = "", Tree* left = nullptr, Tree* right = nullptr);

 	//virtual std::string getFormula() const;
	virtual std::string nodeToString() const;

	virtual void setSymbol(std::string symbol);
	bool hasPriorityOver(PropTree const& t) const;

	static bool isOperatorSymbol(std::string const& s);

protected:
	// This stays in the class and is used only for "hasPriorityOver" function
	char priority;
	std::string symbol;

	typedef std::map<std::string, int> OpMap;
	static OpMap Priorities;
};

#endif

