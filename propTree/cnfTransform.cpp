
#include "cnfTransform.h"


void CnfTransform::replaceEquivalences(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Equivals)
	{
		t->setOperator(PropTree::Operator::And);
		PropTree* newLeft = new PropTree(PropTree::Operator::Implies, t->left, new PropTree(t->right));
		t->right = new PropTree(PropTree::Operator::Implies, t->right, new PropTree(t->left));
		t->left = newLeft;
	}

	if(t->left) replaceEquivalences(t->left);
	if(t->right) replaceEquivalences(t->right);
}

void CnfTransform::replaceImplications(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Implies)
	{
		t->setOperator(PropTree::Operator::Or);
		t->left = new PropTree(PropTree::Operator::Not, t->left);
	}

	if(t->left) replaceImplications(t->left);
	if(t->right) replaceImplications(t->right);
}



void CnfTransform::simplifyNots(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Not) // Here only right is not nullptr
	{
		if(t->right->isVariable())
			return;

		PropTree* oldRight = t->right;
		if(oldRight->getOperator() == PropTree::Operator::Not)
		{
			t->setSymbol(oldRight->right->getSymbol()); // Can be a variable so we set the symbol
			t->left = oldRight->right->left;
			t->right = oldRight->right->right;
		}
		else
		{
			if(oldRight->getOperator() == PropTree::Operator::Or)
				t->setOperator(PropTree::Operator::And);
			else
				t->setOperator(PropTree::Operator::Or);

			PropTree* newLeft = new PropTree(PropTree::Operator::Not, nullptr, oldRight->left);
			PropTree* newRight = new PropTree(PropTree::Operator::Not, nullptr, oldRight->right);
			t->left = newLeft;
			t->right = newRight;
		}

		// deletion of useless children
		oldRight->right = nullptr;
		oldRight->left = nullptr;
		delete(oldRight);
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
	distributeOrOnAnd(t);
}
