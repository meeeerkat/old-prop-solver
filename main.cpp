#include <iostream>
#include "propTree/formulaParsor.h"



int main()
{
	std::string s;
	std::getline(std::cin, s);
	Tree* t = FormulaParsor::getPropTree(s);
	t->display();
	delete(t);
	return 0;
}



