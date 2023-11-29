/*
 * bst.h
 *
 *  Created on: 30/10/2015
 *      Author: clase
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <iostream>


template <class T> class BST;

template <class T>
class Node {
private:
	T value;
	Node *left, *right;

	Node<T>* succesor();

public:
	Node(T);
	Node(T, Node<T>*, Node<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
  	void levelorder(std::stringstream&) const;
  	void ancestors(std::stringstream&, Node<T>* ,T) const;
  	int height(Node<T>*);
	int getLevel(Node<T>*,T,int);
	friend class BST<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri)
	: value(val), left(le), right(ri) {}

template <class T>
void Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			left->add(val);
		} else {
			left = new Node<T>(val);
		}
	} else {
		if (right != 0) {
			right->add(val);
		} else {
			right = new Node<T>(val);
		}
	}
}

template <class T>
bool Node<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
	else{
		return false;
	}
}
template <class T>
int Node<T>::getLevel(Node<T>* prueba,T val,int level) {
 	if (!prueba){
        return 0;
	}
    if (prueba->value == val){
        return level;
	}
    int izquierda = getLevel(prueba->left, val, level + 1);
    if (izquierda != 0){
        return izquierda ;
	}
    int derecha = getLevel(prueba->right, val, level + 1);
    return derecha ;
}
template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) {
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) {
		left = left->left;
		le->left = 0;
		return le;
	}

	Node<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void Node<T>::remove(T val) {
	Node<T> * succ, *old;

	if (val < value) {
		if (left != 0) {
			if (left->value == val) {
				old = left;
				succ = left->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val);
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
    
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}
template <class T>
void Node<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
    aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
    aux << " ";
	}
	aux << value;
}
template <class T>
void Node<T>::levelorder(std::stringstream &aux) const {
  if (left != 0) {
    aux << " ";
    aux << left->value;
		left->levelorder(aux);
	}
	if (right != 0) {
    aux << " ";
    aux << right->value;
		right->levelorder(aux);
	}
}
template <class T>
int Node<T>::height(Node<T>* prueba) {
  if (!prueba)
        return 0;
  else{ 
  int left_height = height(prueba->left);
  int right_height = height(prueba->right);
  if (left_height >= right_height)
    return left_height + 1;
  else
    return right_height + 1;
  }
}
template <class T>
void Node<T>::ancestors(std::stringstream &aux,Node<T>* prueba,T val ) const {
  int i;
  if(val==value){
    i=1+1;
  }
  else{
  aux << value;
  if (val < value) {
		if (left != 0) {
    aux << " ";
  	left->ancestors(aux,prueba,val);
  	}
  }  
    
  if (val > value) {
		if (right != 0) {
    aux << " ";
	   right->ancestors(aux,prueba,val);
	}
  }
  }
}
template <class T>
class BST {
private:
	Node<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	int height();
  	int whatlevelamI(T);
	std::string inorder() const;
	std::string preorder() const;
	std::string postorder() const;
  	std::string levelorder() const;
	std::string visit();
  	std::string ancestors(T val);

};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) {
		if (!root->find(val)) {
			root->add(val);
		}
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}
template <class T>
int BST<T>::height() {
	if (!root) {
		return 0;
	}
  else{
    return root->height(root);
  }
}
template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
    aux << root->value;
		root->levelorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::visit(){ 
std::stringstream aux; 
aux <<preorder()<<"\n";
aux <<inorder()<<"\n";
aux <<postorder()<<"\n";
aux <<levelorder();
return aux.str();
}

template <class T>
std::string BST<T>::ancestors(T val){ 
std::stringstream aux; 
if(find(val)){ 
  std::string a;
  aux <<"[";
  root->ancestors(aux,root,val);
  aux <<"]";
  a=aux.str();
  a.erase(a.size()-2,1);
  return a;
}
  
else{
  aux <<"[]";
  return aux.str();
}
}

template <class T>
int BST<T>::whatlevelamI(T a){
  return root->getLevel(root,a,1);
}
#endif /* BST_H_ */
