#ifndef __CNFTRANSFORM_H_INCLUDED__
#define __CNFTRANSFORM_H_INCLUDED__

#include "propTree.h"


void replaceEquivalences(PropTree* t);
void replaceImplications(PropTree* t);
void simplifyNots(PropTree* t);
void distributeOrOnAnd(PropTree* t);
void toCNF(PropTree* t);

#endif
