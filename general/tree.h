#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include <vector>
#include <string>
#include <iostream>


class Tree {
public:
	Tree(Tree* left = nullptr, Tree* right = nullptr);
 	virtual ~Tree();
	
	// Attributes
	Tree* left = nullptr;
	Tree* right = nullptr;

	// Display
 	virtual std::string nodeToString() const;
	void display(int indent=0, int const& indentSize=4) const;
};


#endif
