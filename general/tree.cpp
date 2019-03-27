#include <iomanip>
#include "tree.h"



Tree::Tree(Tree* left, Tree* right)
	: left(left), right(right)
{

}


Tree::~Tree()
{
	delete(left);
	delete(right);
}






// Display
std::string Tree::nodeToString() const
{
	return "Node";
}

void Tree::display(int indent, int const& indentSize) const
{
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
	std::cout << nodeToString() << "\n ";
        if(left) left->display(indent+indentSize);
        if(right) right->display(indent+indentSize);
}

