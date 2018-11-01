/* readExpression.cpp
 * Author: Bob Kasper
 * Revised: October 2017
 * Description: readExpression function for CSC-2033 Project 3
 * Input: reads an arithmetic expression in infix notation from standard input.
 * Output: a binary tree representing the input expression.
 */
#include <iostream>
#include <string>
#include <cctype>		// for character functions
using namespace std;

#include "LinkedBinaryTree.h"

// lookahead variable holds next character from input
// lookahead is initialized by readExpression
// and updated by readToken function
char lookahead = ' ';  // Note: space will not be part of a token

string readToken() {
	string token = "";	// result to be returned
	int state = 0;		// state 0 = token has no characters
						// state 1 = token has characters
	bool done = false;

	// consume any white space characters before next token
	while (isspace(lookahead)) {
		cin >> lookahead;
	}
	while (!done) {
		switch (lookahead) {
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case ';':
			if (state == 0) { // return symbol as next token
				token += lookahead;
				if (lookahead != ';')
					cin >> lookahead;
			}
			// for state 1, existing token will be returned
			// without adding lookahead character
			done = true;
			break;
		default: 
			if (isspace(lookahead)) {
				if (state == 1)
					done = true;
				else
					cin >> lookahead;
			}
			else {
				// add any other character to token (digit or .)
				state = 1;
				token += lookahead;
				cin >> lookahead;
			}
		} // end switch
	} // end while
	// cout << "token: " << token << endl;
	return token;
}

/* readExpressionRec recursive function
 * Input: reads a sequence of string tokens from standard input.
 * Output: a binary tree representing the input expression.
 * The input string is assumed to be fully parenthesized arithmetic expression in infix notation.
 */
LinkedBinaryTree<string> readExpressionRec(bool parenTerminated = false) {
	// tree objects for root (bt), and left and right subtrees
	LinkedBinaryTree<string> bt, left, right;
	// store current token of input expression
	string tok;
	
	// read an integer string or parenthesized expression
	tok = readToken();
	if ( tok == "(" ) {  // begin reading an embedded expression
		left = readExpressionRec(true);
		}
	else  // the string should be a number
		if (isdigit(tok[0]))
			left.replaceElement(left.root(), tok);
		else {
			// report error and return
			cout << "\nError: integer expected, but found: "
				 << tok << endl;
			left.replaceElement(left.root(), tok);
			return left;
		}
	// read operator or terminator
	tok = readToken();
	switch (tok[0]) {
		case ')': // terminator for subexpression
			if (!parenTerminated)
				cout << "\nWarning: extra right parenthesis" << endl;
			return left;
		case ';': // terminator for entire expression
			if (parenTerminated)
				cout << "\nWarning: missing right parenthesis, found: "
						<< tok << endl;
			return left;
		case '+': // operators
		case '-':
		case '*':
		case '/':
			// place operator at root of tree
			bt.replaceElement(bt.root(), tok);
			bt.replaceLeftSubtree(bt.root(), left);
			// read right operand only after finding an operator
			right = readExpressionRec(parenTerminated);
			bt.replaceRightSubtree(bt.root(), right);
			return bt;
		default:
			cout << "\nError: missing operator, when reading: "
					<< tok << endl;
			return bt;
		} // end switch
} // end readExpressionRec

/* readExpression
 * top-level non-recursive function
 */
LinkedBinaryTree<string> readExpression() {
	// initialize token scanner
	lookahead = ' ';
	return readExpressionRec(false);
}
