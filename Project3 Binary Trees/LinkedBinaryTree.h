/* LinkedBinaryTree.h
 * Authors: Goodrich, Tamassia and Mount (2011)
 * Description: adapted from chapter 7 Code Fragments 7.17 - 7.22
 *              by Bob Kasper
 */
#ifndef LINKED_BINARY_TREE_H
#define LINKED_BINARY_TREE_H true

#include <list> // uses a list of Positions

template <typename Elem>
class LinkedBinaryTree {
protected:
  // Node structure is only for internal use
  struct Node {				// a node in the tree
    Elem  elt;				// the data stored at this node
    Node* parent;			// parent link
    Node* left;				// left child link
    Node* right;			// right child link
    Node() : elt(Elem())	// default constructor
      { parent = left = right = NULL; }
  };

public: // Position objects provide external interface to Nodes
  class Position {	// represents a position in the tree
  private:
    Node* node;					// pointer to the node
  public:
    Position(Node* n = NULL)		// constructor
      { node = n; }
    Elem& operator*() const 		// get element
      { return node->elt; }
	Position left() const			// get left child
	  { return Position(node->left); }
	Position right() const			// get right child
	  {	return Position(node->right); }
	Position parent() const			// get parent
	  { return Position(node->parent); }
	bool isRoot() const 			// root of the tree?
	  { return node->parent == NULL; }
	bool isExternal() const 		// an external node (leaf)?
	  { return node->left == NULL && node->right == NULL; }
    bool isNull() const 		// null position?
      { return node == NULL; }
    friend class LinkedBinaryTree;		// allows direct access to private parts
  };
  typedef std::list<Position> PositionList;

public: // external member functions
	LinkedBinaryTree();					// constructor
	int size() const; 					// number of nodes in tree
	bool isEmpty() const; 				// is tree empty?
	Position root() const; 				// get the root
	PositionList positions() const;		// return list of nodes
	void expandExternal(const Position& p);	    // expand external node
	void replaceElement(const Position& p, const Elem& e);
	// subtree insertion functions
	void replaceLeftSubtree(const Position& p, LinkedBinaryTree<Elem>& subt);
	void replaceRightSubtree(const Position& p, LinkedBinaryTree<Elem>& subt);

private: 			// data members for tree
  Node* theRoot;		// pointer to the root
  int   n;				// number of nodes in tree

protected: 			// protected utility functions
  void preorder(Node* n, PositionList& pl) const; // preorder traversal utility
  Node* nodePtr(const Position& p) const // convert Position to internal Node pointer
    { return p.node; }
};

// Definition of public member functions

// define POSITION as a shorthand name for position type within a tree
#define POSITION typename LinkedBinaryTree<E>::Position

template <typename E>
LinkedBinaryTree<E>::LinkedBinaryTree()	// constructor
    { theRoot = new Node; n = 1; }		// creates tree with a root node

template <typename E>
int LinkedBinaryTree<E>::size() const
    { return n; }

template <typename E>
bool LinkedBinaryTree<E>::isEmpty() const
    { return (size() == 0); }

template <typename E>
// typename LinkedBinaryTree<E>::Position
POSITION LinkedBinaryTree<E>::root() const
    { return POSITION(theRoot); }

template <typename E>
void LinkedBinaryTree<E>::replaceElement(const Position& p, const E& e)
    { *p = e; }

// positions() returns list of all positions in tree
template <typename E>
typename std::list<POSITION> LinkedBinaryTree<E>::positions() const {
	PositionList pl;
	preorder(theRoot, pl);
	return pl;
}

// preorder traversal of tree
// where each node is added to list given by pl
template <typename E>
void LinkedBinaryTree<E>::preorder(Node* n, PositionList& pl) const {
	pl.push_back(Position(n)); // add this node
	if (n->left != NULL)
		preorder(n->left, pl); // traverse left subtree
	if (n->right != NULL)
		preorder(n->right, pl); // traverse right subtree
}

// expand an external node
template <typename E>
void LinkedBinaryTree<E>::expandExternal(const Position& p) {
	Node* pNode = nodePtr(p);
	pNode->left = new Node;
	pNode->left->parent = n;
	pNode->right = new Node;
	pNode->right->parent = n;
	n += 2;
}

// PART 1 TO DO: subtree insertion functions

template <typename E>
void LinkedBinaryTree<E>::replaceLeftSubtree(const Position& p, LinkedBinaryTree<E>& subt) {
		// root of subt becomes left child of p
	Node* newChild = nodePtr(subt.root());
	Node *newParent = nodePtr(p);
	newParent->left = newChild;
	newChild->parent = newParent;
	n += subt.size();
}

template <typename E>
void LinkedBinaryTree<E>::replaceRightSubtree(const Position& p, LinkedBinaryTree<E>& subt) {
	// root of subt becomes right child of p
	Node* newChild = nodePtr(subt.root());
	Node *newParent = nodePtr(p);
	newParent->right = newChild;
	newChild->parent = newParent;
	n += subt.size();
}

#endif // LINKED_BINARY_TREE_H
