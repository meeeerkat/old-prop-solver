#include "propTree.h"


// ARE ATTRIBUTES VIRTUALS ??? (I redefined some of them but they may not be taken into account)


class NotPropTree : public PropTree {
protected:
	const char maxChildrenNumber = 1;
	const char priority = 5;
};

class AndPropTree : public PropTree {
protected:
	const char priority = 4;
};

class OrPropTree : public PropTree {
protected:
	const char priority = 3;
};

class ImpliesPropTree : public PropTree {
protected:
	const char priority = 2;
};

class EquivalsPropTree : public PropTree {
protected:
	const char priority = 1;
};

class VariablePropTree : public PropTree {
protected:
	const char maxChildrenNumber = 0;
};
