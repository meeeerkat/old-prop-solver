#include <vector>
#include <string>

class Tree {
public:
	Tree(std::vector<Tree*> children = std::vector<Tree*>());
 	virtual ~Tree();
	

	// operator<<
	
	virtual void addChild(Tree* const& child);
	virtual Tree* getChild(int const& x) const;
	
 	virtual std::string nodeToString() const;
	virtual std::vector<std::string> getRootToLeafPaths() const;
	void printRootToLeafPaths() const;

protected:
	std::vector<Tree*> children;
};



