#ifndef __CNFTRANSFORM_H_INCLUDED__
#define __CNFTRANSFORM_H_INCLUDED__

#include "propTree.h"

class CnfTransform {
public:
	static void replaceEquivalences(PropTree* t);
	static void replaceImplications(PropTree* t);
	static void simplifyNots(PropTree* t);
	static void distributeOrOnAnd(PropTree* t);
	static void toCNF(PropTree* t);
};

#endif

