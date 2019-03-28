
#include "cnfTransform.h"


void CnfTransform::replaceEquivalences(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Equivals)
	{
		t->setOperator(PropTree::Operator::And);
		PropTree* newLeft = new PropTree(PropTree::Operator::Implies, t->left, new PropTree(static_cast<PropTree*>(t->right)));
		t->right = new PropTree(PropTree::Operator::Implies, t->right, new PropTree(static_cast<PropTree*>(t->left)));
		t->left = newLeft;
	}

	if(t->left) replaceEquivalences(static_cast<PropTree*>(t->left));
	if(t->right) replaceEquivalences(static_cast<PropTree*>(t->right));
}

void CnfTransform::replaceImplications(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Implies)
	{
		t->setOperator(PropTree::Operator::Or);
		t->left = new PropTree(PropTree::Operator::Not, t->left);
	}

	if(t->left) replaceImplications(static_cast<PropTree*>(t->left));
	if(t->right) replaceImplications(static_cast<PropTree*>(t->right));
}



void CnfTransform::simplifyNots(Tree* tree)
{
	PropTree* t = static_cast<PropTree*>(tree);
	if(t->getOperator() == PropTree::Operator::Not) // Here only right is not nullptr
	{
		PropTree* c = static_cast<PropTree*>(t->right);
		if(c->isVariable())
			return;

		if(c->getOperator() == PropTree::Operator::Not)
		{
			c = static_cast<PropTree*>(c->right);
			t->setSymbol(c->getSymbol()); // Can be a variable so we set the symbol
			t->right = c->right;
			t->left = c->left;
		}
		else
		{
			if(c->getOperator() == PropTree::Operator::Or)
				t->setOperator(PropTree::Operator::And);
			else
				t->setOperator(PropTree::Operator::Or);

			t->left = new PropTree(PropTree::Operator::Not, nullptr, c->left);
			t->right = new PropTree(PropTree::Operator::Not, nullptr, c->right);
		}

		// deletion of useless children
		c->right = nullptr;
		c->left = nullptr;
		delete(c);
	}

	if(t->left) simplifyNots(t->left);
	if(t->right) simplifyNots(t->right);
}


void CnfTransform::distributeOrOnAnd(PropTree* t)
{

}


void CnfTransform::toCNF(PropTree* t)
{
	replaceEquivalences(t);
	replaceImplications(t);
	simplifyNots(t);
	/*
	distributeOrOnAnd(t);
	*/
}
