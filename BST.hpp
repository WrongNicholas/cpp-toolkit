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

template <typename T>
class BST {
private:
  TreeNode<T>* root;
  // Private Helper Functions
  TreeNode<T>* get_node(const T& value);
  TreeNode<T>* get_local_min(TreeNode<T>* node) const;
  TreeNode<T>* get_local_max(TreeNode<T>* node) const;
  void in_order_traversal(TreeNode<T>* node);
  void remove(TreeNode<T>*& node, const T& value);
  void clear(TreeNode<T>* node);

public:
  // Constructors and Destructor
  BST() : root(nullptr) {}
  ~BST();
  
  // Accessors
  const bool search(const T& value) const;
  const T& get_min() const;
  const T& get_max() const;
  const T& get_root() const;
  
  // Mutators
  void insert(const T& value);
  void remove(const T& value);
  void clear();
  
  // Utility
  void print();
};

template <typename T>
TreeNode<T>* BST<T>::get_node(const T& value)
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
TreeNode<T>* BST<T>::get_local_min(TreeNode<T>* node) const {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename T>
TreeNode<T>* BST<T>::get_local_max(TreeNode<T>* node) const {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

template <typename T>
void BST<T>::in_order_traversal(TreeNode<T>* node) {
  if (node == nullptr)  return;

  in_order_traversal(node->left);
  std::cout << node->value << " ";
  in_order_traversal(node->right);
}

template <typename T>
void BST<T>::remove(TreeNode<T>*& node, const T& value) {
  if (node == nullptr) return;
  
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
  } else if (node->left == nullptr) {
    TreeNode<T>* temp = node;
    node = node->right;
    delete temp;
  } else if (node->right == nullptr) {
    TreeNode<T>* temp = node;
    node = node->left;
    delete temp;
  } else {
    TreeNode<T>* temp = get_local_min(node->right);
    node->value = temp->value;
    remove(node->right, temp->value);
  }
}


template <typename T>
void BST<T>::clear(TreeNode<T>* node) {
  if (node == nullptr) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

template <typename T>
BST<T>::~BST() {
  clear();
}

template <typename T>
const bool BST<T>::search(const T& value) const {
  return get_node(value) != nullptr;
}

template <typename T>
const T& BST<T>::get_min() const {
  return get_local_min(root)->value;
}

template <typename T>
const T& BST<T>::get_max() const {
  return get_local_max(root)->value;
}

template <typename T>
const T& BST<T>::get_root() const {
  return root->value;
}

template <typename T>
void BST<T>::insert(const T& value) {
  TreeNode<T>* node = new TreeNode<T>(value);
  if (root == nullptr) { root = node; return; }

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
void BST<T>::remove(const T& value) {
  remove(root, value);
}

template <typename T>
void BST<T>::clear() {
  clear(root);
  root = nullptr;
}

template <typename T>
void BST<T>::print() {
  if (root == nullptr) return;

  in_order_traversal(root);
  std::cout << std::endl;
}

#endif