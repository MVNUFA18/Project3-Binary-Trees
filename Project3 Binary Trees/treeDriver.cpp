/* treeDriver.cpp
 * example main function to test the LinkedBinaryTree class
 * using readExpression function to build tree from expression
 */

#include "pch.h"
#include "readExpression.cpp"

// readExpression.cpp includes LinkedBinaryTree.h,
// so you do not need to include it separately here.

// define TPosition as a shorthand type name for positions within a tree
typedef typename LinkedBinaryTree<string>::Position TPosition;

void printExpression(LinkedBinaryTree<string> t, TPosition p) {
	if (!p.isExternal()) {
		cout << "(";
		printExpression(t, p.left());
	}

	cout << p.operator*();

	if (!p.isExternal()) {
		printExpression(t, p.right());
		cout << ")";
	}
}


int main() {
	cout << "Enter an expression: " << endl;
	LinkedBinaryTree<string> etree = readExpression();
	// Testing: print string at root of tree
	cout << "The root element is " << *(etree.root()) << endl;
	// print expression to verify the tree was built correctly
	cout << "The tree represents this expression: ";
	printExpression(etree, etree.root());
	// PART 2 TO DO: evalaute expression and show its value

	// test positions function (keep for Part 1, remove for Part 2)
	list<TPosition> allPositions = etree.positions();
	cout << "\npreOrder: ";
	list<TPosition>::iterator it = allPositions.begin();
	while (it != allPositions.end()) {
		cout << **it << ' ';
		it++;
	}
	cout << endl;
	
	return 0;
}
