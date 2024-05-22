// BinarySearchTree.hpp
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

// Struct defining a node in the binary search tree
template <typename T>
struct TreeNode {
  T value;                    // Value stored in the node
  TreeNode<T>* left;          // Pointer to the left child node
  TreeNode<T>* right;         // Pointer to the right child node
  
  // Constructor to initialize the node with a value
  TreeNode(const T& value) : value(value), left(nullptr), right(nullptr) {}
};

// Class representing a binary search tree
template <typename T>
class BST {
private:
  TreeNode<T>* root;          // Pointer to the root node of the tree

  // Private Helper Functions
  TreeNode<T>* get_node(const T& value);                  // Finds a node with the given value
  TreeNode<T>* get_local_min(TreeNode<T>* node) const;    // Finds the node with the minimum value in a subtree
  TreeNode<T>* get_local_max(TreeNode<T>* node) const;    // Finds the node with the maximum value in a subtree
  void in_order_traversal(TreeNode<T>* node);             // Performs in-order traversal starting from the given node
  void remove(TreeNode<T>*& node, const T& value);        // Recursively deletes all nodes with the given value
  void clear(TreeNode<T>* node);                          // Recursively deletes all nodes in the tree

public:
  // Constructors and Destructor
  BST() : root(nullptr) {}                                // Default constructor
  ~BST();                                                 // Destructor
  
  // Accessors
  const bool search(const T& value) const;                // Searches for a value in the tree
  const T& get_min() const;                               // Returns the minimum value in the tree
  const T& get_max() const;                               // Returns the maximum value in the tree
  const T& get_root() const;                              // Returns the value of the root node
  
  // Mutators
  void insert(const T& value);                            // Inserts a new value into the tree
  void remove(const T& value);                            // Removes a value from the tree
  void clear();                                           // Clears the tree
  
  // Utility
  void print();                                           // Prints all values in the tree (in-order)
};

// Function definitions

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