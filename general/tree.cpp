#include "tree.h"
#include <iomanip>


void Tree::display(int indent, int const& indentSize, bool const& showNull) const
{
        if (indent)
            std::cout << std::setw(indent) << ' ';
	std::cout << nodeToString() << std::endl;

        if(getLeft()) getLeft()->display(indent+indentSize, indentSize, showNull);
	else if(showNull) std::cout << std::setw(indent+indentSize) << ' ' << "null" << std::endl;

        if(getRight()) getRight()->display(indent+indentSize, indentSize, showNull);
	else if(showNull) std::cout << std::setw(indent+indentSize) << ' ' << "null" << std::endl;
}


std::ostream &operator<<(std::ostream &out, Tree const& t)
{
	t.display(0, 4);
	return out;
}
