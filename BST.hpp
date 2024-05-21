// BinarySearchTree.hpp
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <typename T>
struct TreeNode {
  T value;
  TreeNode<T>* left;
  TreeNode<T>* right;
   
  TreeNode(T value) : value(value), left(nullptr), right(nullptr) {}
};
#include <iostream>
template <typename T>
class BST {
private:
  TreeNode<T>* root;
public:
  // Constructor and Destructor
  BST();
  ~BST();
  
  // Mutators
  void insert(const T& value);
  bool search(const T& value);
  void test() {
    std::cout << root->value;
  }
};

template <typename T>
BST<T>::BST() {

}

template <typename T>
BST<T>::~BST() {

}

template <typename T>
void BST<T>::insert(const T& value) {
  TreeNode<T>* node = new TreeNode(value);

  if (root == nullptr) {
    root = node;
    return;
  }

  TreeNode<T>* current = root;
  while (current != nullptr) {
    if (node->value < current->value) {
      current = current->left;
    }
    else if (node->value > current->value) {
      current = current->right;
    }
    else {
      return;
    }
  }

  current = node;
}

template <typename T>
bool BST<T>::search(const T& value) {
  if (root != nullptr) {
    return false;
  }

  TreeNode<T>* current = root;

  while (current != nullptr) {
    if (value < current->value) {
      current = current->left;
    }
    else if (value > current->value) {
      current = current->right;
    }
    else {
      return true;
    }
  }

  return false;
}

#endif
