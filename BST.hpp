// BinarySearchTree.hpp
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

template <typename T>
struct TreeNode {
  T value;
  TreeNode<T>* left;
  TreeNode<T>* right;
   
  TreeNode(const T& value) : value(value), left(nullptr), right(nullptr) {}
};
#include <iostream>
template <typename T>
class BST {
private:
  TreeNode<T>* root;

  void in_order_traversal(TreeNode<T>* node);
  TreeNode<T>* find_node(const T& value);
  void remove(TreeNode<T>*& node, const T& value);
  TreeNode<T>* find_local_min(TreeNode<T>* node);
public:
  BST() : root(nullptr) {}
  ~BST();
  
  void insert(const T& value);
  bool search(const T& value);
  void remove(const T& value);
  
  void print();
};

template <typename T>
void BST<T>::in_order_traversal(TreeNode<T>* node) {
  if (node == nullptr) {
    return;
  }

  in_order_traversal(node->left);
  std::cout << node->value << " ";
  in_order_traversal(node->right);
}

template <typename T>
TreeNode<T>* BST<T>::find_node(const T& value)
{
  TreeNode<T>* current = root;
  while (current != nullptr) {
    if (value < current->value) {
      current = current->left;
    }
    else if (value > current->value) {
      current = current->right;
    }
    else {
      return current;
    }
  }
  return nullptr;
}

template <typename T>
void BST<T>::remove(TreeNode<T>*& node, const T& value) {
  if (node == nullptr) {
    return;
  }

  if (value < node->value) {
    remove(node->left, value);
    return;
  }
  
  if (value > node->value) {
    remove(node->right, value);
    return;
  }

  if (node->left == nullptr && node->right == nullptr) {
    delete node;
    node = nullptr;
    return;
  }

  if (node->left == nullptr) {
    TreeNode<T>* temp = node;
    node = node->right;
    delete temp;
    return;
  }

  if (node->right == nullptr) {
    TreeNode<T>* temp = node;
    node = node->left;
    delete temp;
    return;
  }

  TreeNode<T>* temp = find_local_min(node->right);
  node->value = temp->value;
  remove(node->right, temp->value);
}

template <typename T>
TreeNode<T>* BST<T>::find_local_min(TreeNode<T>* node) {
  while (node->left != nullptr) {
    node = node->left;
  }

  return node;
}

template <typename T>
BST<T>::~BST() {

}

template <typename T>
void BST<T>::insert(const T& value) {
  TreeNode<T>* node = new TreeNode<T>(value);
  if (root == nullptr) {
    root = node;
    return;
  }

  TreeNode<T>* current = root;
  TreeNode<T>* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (value < current->value) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }

  if (value < parent->value) {
    parent->left = node;
  }
  else {
    parent->right = node;
  }
}

template <typename T>
bool BST<T>::search(const T& value) {
  return find_node(value) != nullptr;
}

template <typename T>
void BST<T>::remove(const T& value) {
  remove(root, value);
}

template <typename T>
void BST<T>::print() {
  in_order_traversal(root);
  std::cout << std::endl;
}

#endif