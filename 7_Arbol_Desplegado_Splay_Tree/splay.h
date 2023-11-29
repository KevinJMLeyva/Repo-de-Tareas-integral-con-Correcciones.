#ifndef Splay_H_
#define Splay_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;
template <class T>class SplayTree;

struct Node {
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
	void preorder(std::stringstream &) const;
    void inorder(std::stringstream &) const;
};
typedef Node *NodePtr;

void Node::preorder(std::stringstream &aux) const {
	aux << data;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

void Node::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << data;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
class SplayTree {
private:
    NodePtr root;
    NodePtr searchTreeHelper(NodePtr, T);
    void deleteNodeHelper(NodePtr, T);
    void printHelper(NodePtr, string, bool);
    void leftRotate(NodePtr);
    void rightRotate(NodePtr);
    void splay(NodePtr);
    NodePtr join(NodePtr, NodePtr);
    void split(NodePtr &, NodePtr &, NodePtr &);
public:
    SplayTree();
    std::string preorder();
    std::string inorder();
    bool find(T);
    NodePtr minimum(NodePtr );
    NodePtr maximum(NodePtr );
    NodePtr successor(NodePtr );
    NodePtr predecessor(NodePtr );
    void add(int) ;
    void remove(T);
    void prettyPrint();
};
	template <class T>
    SplayTree<T>::SplayTree() {
		root = nullptr;
	}
    
    template <class T>
	NodePtr SplayTree<T>::searchTreeHelper(NodePtr node, T key) {
		if (node == nullptr || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}
        return searchTreeHelper(node->right, key);
	}

    template <class T>
	void SplayTree<T>::deleteNodeHelper(NodePtr node, T key) {
		NodePtr x = nullptr;
		NodePtr t, s;
		while (node != nullptr){
			if (node->data == key) {
				x = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (x == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		}
		split(x, s, t); // split the tree
		if (s->left){ // remove x
			s->left->parent = nullptr;
		}
		root = join(s->left, t);
		delete(s);
		s = nullptr;
	}

    template <class T>
	void  SplayTree<T>::printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != nullptr) {
		   cout<<indent;
		   if (last) {
		      cout<<"└────";
		      indent += "     ";
		   } else {
		      cout<<"├────";
		      indent += "|    ";
		   }

		   cout<<root->data<<endl;

		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

    template <class T>
	void SplayTree<T>::leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

    template <class T>
	void SplayTree<T>::rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

    template <class T>
	void SplayTree<T>::splay(NodePtr x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig rotation
					rightRotate(x->parent);
				} else {
					// zag rotation
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig rotation
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag rotation
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag rotation
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				// zag-zig rotation
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

    template <class T>
	NodePtr SplayTree<T>::join(NodePtr s, NodePtr t){
		if (!s) {
			return t;
		}

		if (!t) {
			return s;
		}
		NodePtr x = maximum(s);
		splay(x);
		x->right = t;
		t->parent = x;
		return x;
	}
    
    template <class T>
	void SplayTree<T>::split(NodePtr &x, NodePtr &s, NodePtr &t) {
		splay(x);
		if (x->right) {
			t = x->right;
			t->parent = nullptr;
		} else {
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	} 

//publico  
    
    template <class T>	
    std::string SplayTree<T>::preorder()
    {
        std::stringstream aux;
        aux << "[";
       	if(root!=nullptr){
        root->preorder(aux);
		}
        aux << "]";
        return aux.str();
    }
    
    template <class T>		
    std::string SplayTree<T>::inorder() {
		std::stringstream aux;
        aux << "[";
		if(root!=nullptr){
        root->inorder(aux);
		}
        aux << "]";
        return aux.str();
	}
    
    template <class T>	
	bool SplayTree<T>::find(T k) {
		NodePtr x = searchTreeHelper(this->root, k);
		if (x) {
			splay(x);
            return true;
		}
        else{
            return false;
        }
	}
    
    template <class T>	
	NodePtr SplayTree<T>::minimum(NodePtr node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
    
    template <class T>	
	NodePtr SplayTree<T>::maximum(NodePtr node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}
	
    template <class T>	
    NodePtr SplayTree<T>::successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != nullptr) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}
    
    template <class T>	
	NodePtr SplayTree<T>::predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != nullptr) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}
    
    template <class T>	
	void SplayTree<T>::add(int key) {
		// normal BST add
		NodePtr node = new Node;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->data = key;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		// splay the node
		splay(node);
	}
    
    template <class T>	
	void SplayTree<T>::remove(T data) {
		deleteNodeHelper(this->root, data);
	}
    
    template <class T>	
	void SplayTree<T>::prettyPrint() {
		printHelper(this->root, "", true);
	}

#endif /* Splay_H_ */