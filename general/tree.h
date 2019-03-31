#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include <string>
#include <iostream>

class Tree
{
public:
	virtual Tree* getLeft() const = 0;
	virtual Tree* getRight() const = 0;

	// Display
	virtual std::string nodeToString() const = 0;
	virtual void display(int indent, int const& indentSize) const;

   	friend std::ostream &operator<<(std::ostream &out, Tree const& t);
};

#endif
