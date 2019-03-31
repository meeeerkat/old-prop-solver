#ifndef __MODELSTREE_H_INCLUDED__
#define __MODELSTREE_H_INCLUDED__

#include "../clauses/clausesSet.h"



class ModelsTree
{
public:
	ModelsTree(ClausesSet const& c);

	ModelsTree *left, *right;
};

#endif
