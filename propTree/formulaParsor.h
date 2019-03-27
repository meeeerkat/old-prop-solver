#include <string>
#include <vector>


// A static class so internal functions are hidden from the user
// Could have used functions declared in other functions but it's not that clean

// TO MAKE STATIC (SEARCH SYNTAX)

class FormulaParsor
{
public:
 	static PropTree getPropTree(std::string const& formula);

protected:
	static PropTree getPropTreeRecursive(std::string const& formula, int startI, int endI);
};



