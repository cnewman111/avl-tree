//##################################################
// File: AVLTree.h
// Author: Colin Newman
// Description: Header and implementation file for the AVLTree class, which implements a data structure with an efficent search.
//				Unlike the binary tree, the AVL tree is self-balancing and cannot "skew", meaning the worst search time complexity is O(log(n)) rather than O(n).
// Date: October 23, 2021
//#################################################
#ifndef AVL_TREE
#define AVL_TREE
#include <iostream>

template <class T>
struct AVLNode {
	AVLNode<T>* left;
	AVLNode<T>* right;
	T data;
	int height;
	AVLNode() {
		this->left = NULL;
		this->right = NULL;
	}
	AVLNode(T data, AVLNode* l, AVLNode* r, int height = 0) {
		this->data = data;
		this->left = l;
		this->right = r;
		this->height = height;
	}
};

template <class T>
class AVLTree {
protected:
	AVLNode<T>* root;
	void insert(T data, AVLNode<T>*& callingNode);
	void printTree(AVLNode<T>*& callingNode);
	void remove(T data, AVLNode<T>*& callingNode);
	bool contains(T data, AVLNode<T>*& callingNode);
	T findMin(AVLNode<T>*& callingNode);
	T findMax(AVLNode<T>*& callingNode);
	int height(AVLNode<T>* callingNode);
	int max(int int1, int int2);
	void leftRot(AVLNode<T>*& callingNode);
	void rightRot(AVLNode<T>*& callingNode);
	void rebalanceNode(T data, AVLNode<T>*& callingNode);

public:
	AVLTree() { this->root = NULL; }
	bool isEmpty();
	void insert(T data);
	void remove(T data);
	bool contains(T data);
	T findMin();
	T findMax();
	void printTree();
};

//#################################################
// @par Name
// insert()
// @purpose
// Overloaded recursive function which inserts a node in its appropriate place
// @param [in] :
// The data to insert
// @return
// None
// @par References
// None
// @par Notes
// Duplicate data is NOT added again
//###############################################
template <class T>
void AVLTree<T>::insert(T data, AVLNode<T>*& callingNode) {
	//if callingNode is NULL indicating the function has recursed to a leaf, add a node to callingNode
	if (callingNode == NULL) {
		callingNode = new AVLNode<T>(data, NULL, NULL);
	}
	//if the node is not NULL, compare data with its value.  If smaller, go left, if larger or equal go right
	else if (data < callingNode->data) {
		this->insert(data, callingNode->left);
	}
	else if (data > callingNode->data) {
		this->insert(data, callingNode->right);
	}

	this->rebalanceNode(data, callingNode); //Update the height value and perform any necessary rotation.  This will happen bottom up due to the nature of the recursion
}


//#################################################
// @par Name
// remove()
// @purpose
// Overloaded recursive function which removes a node 
// @param [in] :
// The data to remove
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
void AVLTree<T>::remove(T data, AVLNode<T>*& callingNode) {
	if (callingNode == NULL) { 
		throw std::exception("Remove node does not exist");
	}
	else if (data < callingNode->data) {
		remove(data, callingNode->left);
	}
	else if (data > callingNode->data) {
		remove(data, callingNode->right);
	}
	else if ((callingNode->left != NULL) && (callingNode->right != NULL)) { //if the node we want to delete has 2 children, find the smallest value on the right path and set this node equal to it.  Then, delete the smallest value on the right path
		callingNode->data = this->findMin(callingNode->right);
		remove(callingNode->data, callingNode->right);
	}
	//if a base case where the value to delete only has one or no child.  Set the node we want to remove to swap with the child that is not NULL (if it exists), then delete the non NULL child
	else {
		AVLNode<T>* toDelete = callingNode->left ? callingNode->left : callingNode->right;
		if (toDelete == NULL) {
			toDelete = callingNode;
			callingNode = NULL;
		}
		else { //toDelete holds the child that is not NULL
			*callingNode = *toDelete;
		}
		delete toDelete;
	}

	this->rebalanceNode(data, callingNode);
}

//#################################################
// @par Name
// contains()
// @purpose
// Overloaded recursive function which returns true if the data exists in the tree, else false
// @param [in] :
// The data to search for
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
bool AVLTree<T>::contains(T data, AVLNode<T>*& callingNode) {
	if (callingNode == NULL) {
		return false;
	}
	else if (data < callingNode->data) {
		contains(data, callingNode->left);
	}
	else if (data > callingNode->data) {
		contains(data, callingNode->right);
	}
	else { //if it is not NULL, greater than, or less than, we must have arrived at the value
		return true;
	}
}

//#################################################
// @par Name
// findMin()
// @purpose
// Finds the min value in the tree
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// Throws an exception if the tree is empty
//###############################################
template <class T>
T AVLTree<T>::findMin(AVLNode<T>*& callingNode) {
	if (callingNode == NULL) { //indicating the root is NULL, meaning empty list
		throw std::exception("Tree is empty - no min exists.");
	}
	else if (callingNode->left != NULL) {
		return findMin(callingNode->left);
	}
	else {
		return callingNode->data;
	}
}

//#################################################
// @par Name
// findMax()
// @purpose
// Finds the max value in the tree
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// Throws an exception if the tree is empty
//###############################################
template <class T>
T AVLTree<T>::findMax(AVLNode<T>*& callingNode) {
	if (callingNode == NULL) { //indicating the root is NULL, meaning empty list
		throw std::exception("Tree is empty - no maximum exists.");
	}
	else if (callingNode->right != NULL) {
		return findMax(callingNode->right);
	}
	else {
		return callingNode->data;
	}
}

//#################################################
// @par Name
// height
// @purpose
// Determines the height of a node
// @param [in] :
// None
// @return
// Height of the node as an int
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
int AVLTree<T>::height(AVLNode<T>* callingNode) {
	return (callingNode == NULL) ? -1 : callingNode->height;
}

//#################################################
// @par Name
// max()
// @purpose
// Finds the larger of 2 ints
// @param [in] :
// None
// @return
// The larger of the 2 inputs
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
int AVLTree<T>::max(int int1, int int2) {
	return (int1 > int2) ? int1 : int2;
}

//#################################################
// @par Name
// leftRot()
// @purpose
// Performs a left rotation about the input node
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
void AVLTree<T>::leftRot(AVLNode<T>*& callingNode) {
	AVLNode<T>* pivot = callingNode->right;
	AVLNode<T>* temp = pivot->left;
	pivot->left = callingNode;
	callingNode->right = temp;
	callingNode->height = this->max(height(callingNode->left), height(callingNode->right)) + 1;
	pivot->height = this->max(height(pivot->left), height(pivot->right)) + 1;
	callingNode = pivot;
}

//#################################################
// @par Name
// rightRot()
// @purpose
// Performs a right rotation about the input node
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
void AVLTree<T>::rightRot(AVLNode<T>*& callingNode) {
	AVLNode<T>* pivot = callingNode->left;
	AVLNode<T>* temp = pivot->right;
	pivot->right = callingNode;
	callingNode->left = temp;
	callingNode->height = this->max(height(callingNode->left), height(callingNode->right)) + 1;
	pivot->height = this->max(height(pivot->left), height(pivot->right)) + 1;
	callingNode = pivot;
}

//#################################################
// @par Name
// rebalanceNode()
// @purpose
// Updates the height of the input node and performs any necessary rotations
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
void AVLTree<T>::rebalanceNode(T data, AVLNode<T>*& callingNode) {
	if (callingNode != NULL) {
		callingNode->height = this->max(height(callingNode->left), height(callingNode->right)) + 1; //updating the height of the node

		int balanceFactor = height(callingNode->right) - height(callingNode->left);
		if (balanceFactor > 1) { //right heavy
			if (data > callingNode->right->data) { //meaning we have a "right-right" situation and can perform a traditional left rotation
				this->leftRot(callingNode);
			}
			else { //meaning we have a "right-left" sitation
				this->leftRot(callingNode);
				this->rightRot(callingNode);
			}
		}
		else if (balanceFactor < -1) { //left heavy
			if (data < callingNode->left->data) { //meaning we have a "left-left" situation and can perform a traditional right rotation
				this->rightRot(callingNode);
			}
			else { //meaning we have a "left-right" sitatuon
				this->rightRot(callingNode);
				this->leftRot(callingNode);
			}
		}
	}
}

//#################################################
// @par Name
// printTree()
// @purpose
// Prints the contents of the tree in ascending order (small to large)
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
void AVLTree<T>::printTree(AVLNode<T>*& callingNode) {
	if (callingNode == NULL) {
		return;
	}
	this->printTree(callingNode->left);
	std::cout << callingNode->data << std::endl;
	this->printTree(callingNode->right);
}

//#################################################
// @par Name
// isEmpty()
// @purpose
// Returns true if the tree is empty, else false
// @param [in] :
// None
// @return
// None
// @par References
// None
// @par Notes
// None
//###############################################
template <class T>
bool AVLTree<T>::isEmpty() {
	if (this->root == NULL) {
		return true;
	}
	else {
		return false;
	}
}

//#################################################
// @par Name
// functions insert() through printTree()
// @purpose
// User accesable functions which are designed to call their corresponding overloaded function in the private section.  
// @param [in] :
// See documentation in private section
// @return
// See documentation in private section
// @par References
// None
// @par Notes
// See documentation in private section
//###############################################
template <class T>
void AVLTree<T>::insert(T data) {
	this->insert(data, this->root);
}

template <class T>
void AVLTree<T>::remove(T data) {
	this->remove(data, this->root);
}

template <class T>
bool AVLTree<T>::contains(T data) {
	return contains(data, this->root);
}

template <class T>
T AVLTree<T>::findMin() {
	return findMin(this->root);
}

template <class T>
T AVLTree<T>::findMax() {
	return findMax(this->root);
}

template <class T>
void AVLTree<T>::printTree() {
	this->printTree(this->root);
}

#endif // !AVL_TREE
