#pragma warning
#ifndef TREENODE_H
#define TREENODE_H

#include <string.h>
#include <iostream>

class TreeNode
{
	private:
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
		char* c;
	
	public:
		TreeNode(TreeNode*, char*);
		TreeNode(TreeNode*, TreeNode*, char*);
		TreeNode(TreeNode*, TreeNode*, TreeNode*, char*);
		char* getChar();
		void setChar(char*);
		
		TreeNode* getParent();
		void setParent(TreeNode*);
		
		TreeNode* getLeft();
		void setLeft(TreeNode*);
		
		TreeNode* getRight();
		void setRight(TreeNode*);
};

#endif