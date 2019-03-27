#include <string>
#include "../general/tree.h"


class PropTree : public Tree {
public:
	PropTree(std::vector<PropTree*> children);

	// operator<<

	virtual std::string getFormula() const;

protected:
	const char maxChildrenNumber = -1;
	const char priority = 0;
};



