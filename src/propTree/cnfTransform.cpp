#include <iostream>
#include "cnfTransform.h"


void replaceEquivalences(PropTree* t)
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

void replaceImplications(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Implies)
	{
		t->setOperator(PropTree::Operator::Or);
		t->left = new PropTree(PropTree::Operator::Not, nullptr, t->left); // Not has only the right child
	}

	if(t->left) replaceImplications(t->left);
	if(t->right) replaceImplications(t->right);
}



void simplifyNots(PropTree* t)
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


void distributeOrOnAnd(PropTree* t)
{
	if(t->getOperator() == PropTree::Operator::Or)
	{
		if(t->right->getOperator() == PropTree::Operator::And && t->left->getOperator() == PropTree::Operator::And)
		{
			t->setOperator(PropTree::Operator::And);
			
			PropTree* leftLeft = t->left->left;
			PropTree* leftRight = t->left->right;
			t->left->left = new PropTree(PropTree::Operator::Or, t->left->left, t->right->left);
			t->left->right = new PropTree(PropTree::Operator::Or, new PropTree(leftLeft), t->right->right);
			t->right->left = new PropTree(PropTree::Operator::Or, leftRight, new PropTree(t->right->left));
			t->right->right = new PropTree(PropTree::Operator::Or, new PropTree(leftRight), new PropTree(t->right->right));
		}
		else
		{
			PropTree *andTree=nullptr, *literal=nullptr;
			if(t->left->getOperator() == PropTree::Operator::And && t->right->isLiteral())
			{
				andTree = t->left;
				literal = t->right;
			}
			else if(t->right->getOperator() == PropTree::Operator::And && t->left->isLiteral())
			{
				andTree = t->right;
				literal = t->left;
			}

			if(literal) // If we had one of thoses condition satisfied
			{
				t->setOperator(PropTree::Operator::And);
				t->left = new PropTree(PropTree::Operator::Or, andTree->left, literal);
				t->right = new PropTree(PropTree::Operator::Or, andTree->right, new PropTree(literal));
			}
		}
	}

	if(t->left) distributeOrOnAnd(t->left);
	if(t->right) distributeOrOnAnd(t->right);
}


void toCNF(PropTree* t)
{
	replaceEquivalences(t);
	replaceImplications(t);
	simplifyNots(t);
	distributeOrOnAnd(t);
}
