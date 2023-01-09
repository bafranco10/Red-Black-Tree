// FILE: Rbt.cpp
// Brian Franco, Transy U
// CS 2444, Fall 2021
//
// implementation Red Black Tree
//
#include "Rbt.h"
// constructor,destructor
Rbt::Rbt (void) {
	treeRoot = 0; 
 }
Rbt::~Rbt(void) { 
postOrder (treeRoot); 
}
//
// mutator
// calls private overload function
// stores return value in local variable
bool Rbt::put (const ValueType& newItem) {
	bool returnValue; 
	returnValue = put (treeRoot, newItem);
	// makes sure that whole tree root is always black 
	treeRoot -> isRed = false;
	return returnValue; 
}
// private overload recursive function 
// put calls itself and recursively inserts new nodes
bool Rbt::put (Node*&root, const ValueType& newItem) {
	// local variable to hold return value
	bool returnValue; 
	// base case
	if (root == 0) {
		root = new Node; 
		root -> isRed = true; 
		root -> right = 0;
		root -> left = 0;
		root -> data = newItem;
		return true; 
	}
	// base case
	if (root -> data == newItem) {
		return false; 
	}
	// recursive cases 
	// check for split
	split (root); 
	if (root -> data > newItem) {
		returnValue = put (root -> left, newItem); 
	}
	else {
		returnValue = put (root -> right, newItem);
	}
	// check for rebalance
	rebalance (root); 
	// returns value
	return returnValue; 
}
// split function that splits a red box 
// checks to see if we have a full red box
void Rbt::split (Node*root) {
	if (root && root -> left && root -> right && root -> isRed == false && root -> left -> isRed == true && root -> right -> isRed == true) {
		root -> isRed = true; 
		root -> right -> isRed = false;
		root -> left -> isRed = false;
	}
}
// rebalance that rebalances the nodes in a mini tree
// checks for which condition is violated to trigger a rebalance and then calls corresponding function 
void Rbt::rebalance (Node*& root) {
	if (root -> left != 0 && root -> left -> isRed == true && root -> left -> left != 0 && root -> left -> left -> isRed == true) {
		leftLeft (root); 
	}
	if (root -> left != 0 && root -> left -> isRed == true && root -> left -> right != 0 && root -> left -> right -> isRed == true) {
		leftRight (root);
	}
	if (root -> right != 0 && root -> right -> isRed == true && root -> right -> right != 0 && root -> right -> right -> isRed == true) {
		rightRight (root);
	}
	if (root -> right != 0 && root -> right -> isRed == true && root -> right -> left != 0 && root -> right -> left -> isRed == true) {
		rightRight (root); 
	}
	return; 
}
// rebalance function for two red arrows in a row; 
// only works if root -> right and root -> right -> right are red
void Rbt::rightRight (Node*& root) {
	Node *temp;
	temp = root;
	root = temp -> right; 
	temp -> right = root -> left;
	root -> left = temp;
	root -> isRed = false;
	root -> left -> isRed = true;
	return;
}
// rebalance function for two red arrows in a row (right and then left)
// only works if root -> right and root -> right -> left are red
void Rbt::rightLeft (Node*& root) {
	Node *temp; 
	temp = root;
	root = temp -> right -> left; 
	temp -> right -> left = root -> right; 
	root -> right = temp -> right; 
	temp -> right = root -> left; 
	root -> left = temp; 
	root -> isRed = false;
	root -> left -> isRed = true; 
	return; 
}
// rebalance function for two red arrows in a row (left and then left)
// only works if root -> left and root -> left -> left are red
void Rbt::leftLeft (Node*& root) {
	Node *temp;
	temp = root;
	root = temp -> left; 
	temp -> left = root -> right;
	root -> right = temp; 
	root -> isRed = false; 
	root -> right -> isRed = true;
	return; 
}
// rebalance function for 2 red arrows in a row (left then right)
// only works if root -> left and root -> left -> right are red
void Rbt::leftRight (Node*& root) {
	Node *temp;
	temp = root;
	root = temp -> left -> right;
	temp -> left -> right = root -> left; 
	root -> left = temp -> left; 
	temp -> left = root -> right;
	root -> right = temp;
	root -> isRed = false;
	root -> right -> isRed = true;
	return;
}

// accessors
// gets item in the list
// calls private overload
bool Rbt::get (const KeyType& searchKey, ValueType& foundItem) const {
	return get (treeRoot,searchKey,foundItem); 
}
// private overload recursive function 
// get calls itself and recursively gets new nodes
bool Rbt::get (Node*root, const KeyType& searchKey, ValueType& foundItem) const {
	// base case
	if (root == 0 ) {
		return false; 
	}
	// base case
	if (root -> data == searchKey) { 
		foundItem = root -> data; 
		return true; 
	}
	// check where to get item from
	if (searchKey < root -> data) {
	return get (root -> left, searchKey, foundItem);
	}
	else  {
	return get (root -> right, searchKey, foundItem); 
	}
}

// print Debug 
void Rbt::printDEBUG (void) const {
	// if list is empty say it is empty
	if (treeRoot == 0) {
		cout << endl << " No contents in Rbt";
	}
	// print list in preorder
	preOrder (treeRoot); 
}
// recursively goes down the list order
// preorder traversal
bool Rbt::preOrder (Node *treeRoot) const {
	// if there is nothing then return false
	if (treeRoot == 0) {
		return false; 
	}
	// calls print function so we can see what is called
	printNode(treeRoot);
	// go down the left first
	preOrder (treeRoot -> left);
	// then go down the right 
	preOrder (treeRoot -> right); 
	return true; 
}

#define DB
/// print Node
// display the current contents of a Node with color
// [includes DB debugging option]
//
void Rbt::printNode (Node *treeRoot) const {
#ifndef DB 
	cout << treeRoot -> data << ' '; 
#else 
	cout << endl << "data; " << treeRoot -> data; 
	cout << endl << "\tleft: ";
	if (treeRoot -> left) {
		cout << treeRoot -> left -> data; 
	}
	else {
		cout << "[EXTERNAL]";
	}
	cout << endl << "\tright: ";
	if (treeRoot -> right) {
		cout << treeRoot -> right -> data; 
	}
	else {
		cout << "[EXTERNAL]";
	}
	cout << endl << "\tColor: "; 
	if (treeRoot -> isRed == true) {
		cout << "Red"; 
	}
	else {
		cout << "Black"; 
	}
	cout << endl; 
	#endif 
}
// post order traversal for destructor where visiting a node deletes it
bool Rbt::postOrder (Node *root) const {
	if (root == 0) {
		return false; 
	}
	postOrder (root -> left);
	postOrder (root -> right);
	delete root; 
	return true; 
}