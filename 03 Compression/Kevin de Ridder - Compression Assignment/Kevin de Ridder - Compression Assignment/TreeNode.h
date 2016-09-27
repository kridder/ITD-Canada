#pragma once

class TreeNode
{
public:
	// member functions
	TreeNode()
	{
		hasChildren = false;
		character = 0;
		left = 0;
		right = 0;
	} // end default constructor

	TreeNode(char character)
	{
		hasChildren = false;
		this->character = character;
		left = 0;
		right = 0;
	} // end leaf constructor

	TreeNode(TreeNode * left, TreeNode * right)
	{
		hasChildren = true;
		character = 0;
		this->left = left;
		this->right = right;
	} // end branch constructor

	~TreeNode()
	{

	} // end destructor

	// data members
	bool hasChildren;
	char character;
	TreeNode * left;
	TreeNode * right;
};