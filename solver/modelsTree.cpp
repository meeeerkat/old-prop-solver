#include "modelsTree.h"



ModelsTree::ModelsTree(ClausesSet const& c)
{

}

ModelsTree::~ModelsTree()
{
	delete(left);
	delete(right);
}

// For base Tree class
Tree* ModelsTree::getLeft() const {return left;}
Tree* ModelsTree::getRight() const {return right;}
std::string ModelsTree::nodeToString() const
{
	return "";
}





