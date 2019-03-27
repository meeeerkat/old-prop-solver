#include <iostream>
#include "tree.h"



Tree::Tree(std::vector<Tree*> children)
	: children(children)
{

}


Tree::~Tree()
{
	for(unsigned int i=0; i < children.size(); i++)
		delete(children[i]);
}



void Tree::addChild(Tree* const& child)
{
	children.push_back(child);
}


Tree* Tree::getChild(int const& x) const
{
	return children[x];
}


std::string Tree::nodeToString() const
{
	return "Node";
}

std::vector<std::string> Tree::getRootToLeafPaths() const
{
	if (children.size() == 0)
		return std::vector<std::string>({nodeToString()});

	std::string rootString = nodeToString();

	std::vector<std::string> out = std::vector<std::string>();
	for(unsigned int x=0; x < children.size(); x++)
	{
		std::vector<std::string> childPaths = children[x]->getRootToLeafPaths();
		for(unsigned int y=0; y < childPaths.size(); y++)
			out.push_back(rootString + " -> " + childPaths[y]);
	}

	return out;
}

void Tree::printRootToLeafPaths() const
{
	std::vector<std::string> paths = getRootToLeafPaths();
	for(unsigned int i=0; i < paths.size(); i++)
		std::cout << paths[i] << std::endl;
}
