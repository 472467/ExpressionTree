#include "treeNode.h"


TreeNode::TreeNode(TreeNode* p, char* n){
	c = n;
	parent = p;
	left = NULL;
	right = NULL;
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, char* n){
	c = n;
	parent = p;
	left = l;
	right = NULL;
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, char* n){
	c = n;
	parent = p;
	left = l;
	right = r;
}

char* TreeNode::getChar(){
	return c;
}
void TreeNode::setChar(char*  n){
	c = n;
}

TreeNode* TreeNode::getParent(){
	return parent;
}
void TreeNode::setParent(TreeNode* p){
	parent = p;
}

TreeNode* TreeNode::getLeft(){
	return left;
}
void TreeNode::setLeft(TreeNode* l){
	left = l;
}

TreeNode* TreeNode::getRight(){
	return right;
}
void TreeNode::setRight(TreeNode* r){
	right = r;
}