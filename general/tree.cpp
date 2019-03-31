#include "tree.h"
#include <iomanip>


void Tree::display(int indent, int const& indentSize) const
{
        if (indent)
            std::cout << std::setw(indent) << ' ';
	std::cout << nodeToString() << std::endl;
        if(getLeft()) getLeft()->display(indent+indentSize, indentSize);
        if(getRight()) getRight()->display(indent+indentSize, indentSize);
}


std::ostream &operator<<(std::ostream &out, Tree const& t)
{
	t.display(0, 4);
	return out;
}
