// BinaryTreeImplementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;
//************** TreeNode Class *****************
class TreeNode
{
private:
	int* Data;
	TreeNode* Left;
	TreeNode* Right;
public:
	TreeNode();
	TreeNode(int*);
	int* GetData();
	void SetData(int*);
	TreeNode* GetLeft();
	void SetLeft(TreeNode*);
	TreeNode *GetRight();
	void SetRight(TreeNode*);
	bool IsLeaf();
};//End of class
//************** TreeNode Constructers *****************
TreeNode::TreeNode()
{
	this->Data = NULL;
	this->Left = NULL;
	this->Right = NULL;
}
TreeNode::TreeNode(int* Data)
{
	this->Data = Data;
	this->Left = NULL;
	this->Right = NULL;
}
int* TreeNode::GetData()
{
	return this->Data;
}

void TreeNode::SetData(int* data)
{
	Data = data;
}
TreeNode* TreeNode::GetLeft()
{
	return Left;
}

void TreeNode::SetLeft(TreeNode* left)
{
	Left = left;
}
TreeNode* TreeNode::GetRight()
{
	return Right;
}

void TreeNode::SetRight(TreeNode* right)
{
	Right = right;
}
bool TreeNode::IsLeaf()
{
	if (this->Left == NULL && this->Right == NULL)
		return true;

	else
		return false;
}
//************** TreeNode Insertion *****************
void InsertNode(TreeNode* root, int* info)
{
	TreeNode* node = new TreeNode(info);
	TreeNode *p, *q;
	p = q = root;
	while (*info != *(p->GetData()) && q != NULL)
	{
		p = q;
		if (*info < *(p->GetData()))
			q = p->GetLeft();
		else
			q = p->GetRight();
	}
	if (*info == *(p->GetData())){
		cout << "You are attempting insert duplicate node!!! " << *info << endl;
		delete node;
	}
	else if (*info < *(p->GetData()))
		p->SetLeft(node);
	else
		p->SetRight(node);
}
//************** Preorder *****************
void PreOrder(TreeNode* treeNode)
{
	if (treeNode != NULL)
	{
		cout << *(treeNode->GetData()) << " ";
		PreOrder(treeNode->GetLeft());
		PreOrder(treeNode->GetRight());
	}
}
void InOrder(TreeNode* treeNode)
{
	if (treeNode != NULL)
	{
		InOrder(treeNode->GetLeft());
		cout << *(treeNode->GetData()) << " ";
		InOrder(treeNode->GetRight());
	}
}
void PostOrder(TreeNode* treeNode)
{
	if (treeNode != NULL)
	{
		PostOrder(treeNode->GetLeft());
		PostOrder(treeNode->GetRight());
		cout << *(treeNode->GetData()) << " ";
	}
}
//************** TreeNode FindMinimum *****************
TreeNode* FindMinimum(TreeNode* tree)
{
	if (tree == NULL)
		return NULL;
	if (tree->GetLeft() == NULL)
		return tree;
	return FindMinimum(tree->GetLeft());
}
//************** TreeNode DeleteMethod *****************
TreeNode* DeleteNode(TreeNode* tree, int node)
{
	TreeNode* temp;
	int compare = node - *(tree->GetData());

	if (compare < 0)
	{
		temp = DeleteNode(tree->GetLeft(), node);
		tree->SetLeft(temp);
	}
	else if (compare > 0)
	{
		temp = DeleteNode(tree->GetRight(), node);
		tree->SetRight(temp);
	}
	//two children, replace with inorder successor
	else if (tree->GetLeft() != NULL &&
		tree->GetRight() != NULL)
	{
		TreeNode* minNode;
		minNode = FindMinimum(tree->GetRight());
		tree->SetData(minNode->GetData());
		temp = DeleteNode(tree->GetRight(), *(minNode->GetData()));
		tree->SetRight(temp);
	}
	else {  // case 1
		TreeNode* nodeToDelete = tree;
		if (tree->GetLeft() == NULL) //will handle 0 children
			tree = tree->GetRight();
		else if (tree->GetRight() == NULL)
			tree = tree->GetLeft();
		else tree = NULL;
		delete nodeToDelete;
	}
	return tree;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int nodes[] = { 10, 8, 12, 6, 9, 11, 14 };

	TreeNode* root = new TreeNode();
	root->SetData(&nodes[0]);

	for (int i = 1; nodes[i]>0; i++)
	{
		InsertNode(root, &nodes[i]);
	}
	cout << "\n---------- Pre-Order ----------\n ";
	PreOrder(root);
	cout << "\n\n---------- In-Order ----------\n ";
	InOrder(root);
	cout << "\n\n---------- Post-Order ----------\n ";
	PostOrder(root);
	cout << "\n\n---------- FindMinimum ----------\n ";
	cout << *FindMinimum(root)->GetData() << endl;
	cout << "\n\n---------- Delete Node ----------\n ";
	cout << *DeleteNode(root, 9)->GetData() << endl;

	cout << "\n\n";
	return 0;
}

