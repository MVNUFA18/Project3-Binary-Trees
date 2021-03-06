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

double evaluateExpression(LinkedBinaryTree<string> t, TPosition p) {
	if (p.isExternal()) {
		return atof((p.operator*()).c_str());
	}
	else {
		double x = evaluateExpression(t, p.left());
		double y = evaluateExpression(t, p.right());

		 if (p.operator*() == "+") {
				return x + y;
		}
		else if (p.operator*() == "-") {
				return x - y;
		}
		else if (p.operator*() == "*") {
			return x * y;
		}
		else if (p.operator*() == "/") {
			return x / y;
		}
	}
	return 0;
}


int main() {
	cout << "Enter an expression: " << endl;
	LinkedBinaryTree<string> etree = readExpression();
	// Testing: print string at root of tree

	cout << "The root element is " << *(etree.root()) << endl;
	// print expression to verify the tree was built correctly

	cout << "The tree represents this expression: ";
	printExpression(etree, etree.root());
	cout << " = " << evaluateExpression(etree, etree.root());

	return 0;
}
