//##################################################
// File: AVLTree.h
// Author: Colin Newman
// Description: Test file for the AVLTree class
// Date: October 23, 2021
//#################################################
#include <iostream>
#include "AVLTree.h"
using namespace std;

int main() {
	cout << "Testing the AVLTree class" << endl;
	AVLTree<double> T2;
	cout << "Declaring an AVL object and calling isEmpty() on it" << endl;
	cout << "T2.isEmpty(): ";
	T2.isEmpty() ? cout << "True" << endl : cout << "False" << endl;
	cout << "Adding and removing in this order, then outputting the list (should output in ascending order): Add 3.8, add 20, add -5, add 3, remove 3.8, add 2, add .119, add 100, add 200." << endl;
	T2.insert(3.8);
	T2.insert(20);
	T2.insert(-5);
	T2.insert(3);
	T2.remove(3.8);
	T2.insert(2);
	T2.insert(.119);
	T2.insert(100);
	T2.insert(200);
	T2.printTree();
	cout << "Calling isEmpty() again" << endl;
	cout << "T2.isEmpty(): ";
	T2.isEmpty() ? cout << "True" << endl : cout << "False" << endl;
	cout << "Max: " << T2.findMax() << endl;
	cout << "Min: " << T2.findMin() << endl;
	cout << "Contains 3.78?: ";
	T2.contains(3.78) ? cout << "True" << endl : cout << "False" << endl;
	cout << "Contains .119?: ";
	T2.contains(.119) ? cout << "True" << endl : cout << "False" << endl;
}
