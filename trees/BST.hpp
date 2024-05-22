// BinarySearchTree.hpp
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>

// Struct defining a node in the binary search tree
template <typename Key, typename Value>
struct TreeNode {
  Key key;
  Value value;                     // Value stored in the node
  TreeNode<Key, Value>* left;      // Pointer to the left child node
  TreeNode<Key, Value>* right;     // Pointer to the right child node
  
  // Constructor to initialize the node with a value
  TreeNode(const Key& key, const Value& value) : key(key), value(value), left(nullptr), right(nullptr) {}
};

// Class representing a binary search tree
template <typename Key, typename Value>
class BST {
private:
  TreeNode<Key, Value>* root;          // Pointer to the root node of the tree

  // Private Helper Functions
  TreeNode<Key, Value>* get_node(const Key& key);                         // Finds a node with the given key
  const TreeNode<Key, Value>* get_node(const Key& key) const;             // Finds a node with the given key
  TreeNode<Key, Value>* get_local_min(TreeNode<Key, Value>* node) const;  // Finds the node with the minimum key in a subtree
  TreeNode<Key, Value>* get_local_max(TreeNode<Key, Value>* node) const;  // Finds the node with the maximum key in a subtree
  void in_order_traversal(TreeNode<Key, Value>* node);                    // Performs in-order traversal starting from the given node
  void remove(TreeNode<Key, Value>*& node, const Key& key);               // Recursively deletes all nodes with the given tree
  void clear(TreeNode<Key, Value>* node);                                 // Recursively deletes all nodes in the tree

public:
  // Constructors and Destructor
  BST() : root(nullptr) {}                                                // Default constructor
  ~BST();                                                                 // Destructor
  
  // Accessors
  Value& search(const Key& key);                                          // Returns the value associated with the given key from the tree
  const Value& search(const Key& key) const;                              // Returns the value associated with the given key from the tree (const)
  const Value& get_min() const;                                           // Returns the minimum value in the tree
  const Value& get_max() const;                                           // Returns the maximum value in the tree
  const Value& get_root() const;                                          // Returns the value of the root node
  
  // Mutators
  void insert(const Key& key, const Value& value);                        // Inserts a new key-value pair into the tree
  void remove(const Key& key);                                            // Removes a key-value pair from the tree
  void clear();                                                           // Clears the tree
  
  // Utility
  void print();                                                           // Prints all key-value pairs in the tree (in-order)
};

// Function definitions

template <typename Key, typename Value>
TreeNode<Key, Value>* BST<Key, Value>::get_node(const Key& key)
{
  TreeNode<Key, Value>* current = root;
  while (current != nullptr) {
    if (key < current->key) {
      current = current->left;
    }
    else if (key > current->key) {
      current = current->right;
    }
    else {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename Value>
const TreeNode<Key, Value>* BST<Key, Value>::get_node(const Key& key) const
{
  TreeNode<Key, Value>* current = root;
  while (current != nullptr) {
    if (key < current->key) {
      current = current->left;
    }
    else if (key > current->key) {
      current = current->right;
    }
    else {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename Value>
TreeNode<Key, Value>* BST<Key, Value>::get_local_min(TreeNode<Key, Value>* node) const {
  while (node->left != nullptr) {
    node = node->left;
  }
  return node;
}

template <typename Key, typename Value>
TreeNode<Key, Value>* BST<Key, Value>::get_local_max(TreeNode<Key, Value>* node) const {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

template <typename Key, typename Value>
void BST<Key, Value>::in_order_traversal(TreeNode<Key, Value>* node) {
  if (node == nullptr)  return;

  in_order_traversal(node->left);
  std::cout << "(" << node->key << ", " << node->value << ") ";
  in_order_traversal(node->right);
}

template <typename Key, typename Value>
void BST<Key, Value>::remove(TreeNode<Key, Value>*& node, const Key& key) {
  if (node == nullptr) return;
  
  if (key < node->key) {
    remove(node->left, key);
    return;
  }

  if (key > node->key) {
    remove(node->right, key);
    return;
  } 
  
  if (node->left == nullptr && node->right == nullptr) {
    delete node;
    node = nullptr;
  } else if (node->left == nullptr) {
    TreeNode<Key, Value>* temp = node;
    node = node->right;
    delete temp;
  } else if (node->right == nullptr) {
    TreeNode<Key, Value>* temp = node;
    node = node->left;
    delete temp;
  } else {
    TreeNode<Key, Value>* temp = get_local_min(node->right);
    node->key = temp->key;
    node->value = temp->value;
    remove(node->right, temp->key);
  }
}


template <typename Key, typename Value>
void BST<Key, Value>::clear(TreeNode<Key, Value>* node) {
  if (node == nullptr) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

template <typename Key, typename Value>
BST<Key, Value>::~BST() {
  clear();
}

template <typename Key, typename Value>
Value& BST<Key, Value>::search(const Key& key) {
  return get_node(key)->value;
}

template <typename Key, typename Value>
const Value& BST<Key, Value>::search(const Key& key) const {
  return get_node(key)->value;
}

template <typename Key, typename Value>
const Value& BST<Key, Value>::get_min() const {
  return get_local_min(root)->value;
}

template <typename Key, typename Value>
const Value& BST<Key, Value>::get_max() const {
  return get_local_max(root)->value;
}

template <typename Key, typename Value>
const Value& BST<Key, Value>::get_root() const {
  return root->value;
}

template <typename Key, typename Value>
void BST<Key, Value>::insert(const Key& key, const Value& value) {
  TreeNode<Key, Value>* node = new TreeNode<Key, Value>(key, value);
  if (root == nullptr) { root = node; return; }

  TreeNode<Key, Value>* current = root;
  TreeNode<Key, Value>* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (key < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }

  if (key < parent->key) {
    parent->left = node;
  }
  else {
    parent->right = node;
  }
}

template <typename Key, typename Value>
void BST<Key, Value>::remove(const Key& key) {
  remove(root, key);
}

template <typename Key, typename Value>
void BST<Key, Value>::clear() {
  clear(root);
  root = nullptr;
}

template <typename Key, typename Value>
void BST<Key, Value>::print() {
  if (root == nullptr) return;

  in_order_traversal(root);
  std::cout << std::endl;
}

#endif