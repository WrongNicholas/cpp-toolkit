// AVLTree.hpp
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <stdexcept>

// Struct defining a node in the AVL tree
template <typename Key, typename Value>
struct AVLTreeNode {
  Key key;                            // Key stored in the node
  Value value;                        // Value stored in the node
  int height;                         // Height of the node in the tree

  AVLTreeNode<Key, Value>* left;      // Pointer to the left child node
  AVLTreeNode<Key, Value>* right;     // Pointer to the right child node

  // Constructor to initialize the node with a key and value
  AVLTreeNode(const Key& key, const Value& value) : key(key), value(value), height(0), left(nullptr), right(nullptr) {}
};

// Class representing an AVL tree
template <typename Key, typename Value>
class AVLTree {
private:
  AVLTreeNode<Key, Value>* root;      // Pointer to the root of the tree
  int tree_size;                      // Stores number of key-value pairs in the tree

  // Private Helper Functions
  AVLTreeNode<Key, Value>* search(AVLTreeNode<Key, Value>* node, const Key& key);                       // Finds a node with the given key
  AVLTreeNode<Key, Value>* search(AVLTreeNode<Key, Value>* node, const Key& key) const;                 // Finds a node with the given key (const)
  const AVLTreeNode<Key, Value>* contains(AVLTreeNode<Key, Value>* node, const Key& key) const;         // Finds a node, but returns nullptr instead of throwing exception
  
  const int get_height(AVLTreeNode<Key, Value>* node) const;                                            // Returns the height of the node
  void update_height(AVLTreeNode<Key, Value>* node);                                                    // Updates the height of the node
  const int get_balance(AVLTreeNode<Key, Value>* node) const;                                           // Returns the balance factor of the given node
  AVLTreeNode<Key, Value>* get_local_min(AVLTreeNode<Key, Value>* node);

  AVLTreeNode<Key, Value>* rotate_left(AVLTreeNode<Key, Value>* x);                                     // Performs a left rotation around the given node
  AVLTreeNode<Key, Value>* rotate_right(AVLTreeNode<Key, Value>* y);                                    // Performs a right rotation around the given node
  
  AVLTreeNode<Key, Value>* insert(AVLTreeNode<Key, Value>* node, const Key& key, const Value& value);   // Inserts a new key-value pair into the tree
  AVLTreeNode<Key, Value>* remove(AVLTreeNode<Key, Value>* node, const Key& key);                       // Removes a key-value pair from the tree
  
  // Utility
  void clear(AVLTreeNode<Key, Value>* node);                                                            // Recursively deletes all nodes in the tree

  void print_node(AVLTreeNode<Key, Value>* node);                                                       // Prints the given node
  void in_order(AVLTreeNode<Key, Value>* node);                                                         // Performs in-order traversal starting from the given node
  void pre_order(AVLTreeNode<Key, Value>* node);                                                        // Performs pre-order traversal starting from the given node
  void post_order(AVLTreeNode<Key, Value>* node);                                                       // Performs post-order traversal starting from the given node
public:
  // Constructor and Destructor
  AVLTree() : root(nullptr), tree_size(0) {}                                                            // Default constructor
  ~AVLTree();                                                                                           // Destructor
  // Accessors
  Value& search(const Key& key);                                                                        // Returns the value associated with the given key from the list
  const Value& search(const Key& key) const;                                                            // Returns the value associated with the given key from the list (const)
  const bool contains(const Key& key) const;                                                            // Returns if the given key exists in the list
  const bool empty() const;                                                                             // Returns if the list is empty
  const int size() const;                                                                               // Returns the size of the list
  const int height() const;

  // Mutators
  void insert(const Key& key, const Value& value);                                                      // Inserts a new key-value pair into the tree
  void remove(const Key& key);                                                                          // Removes a key-value pair from the tree
  void replace(const Key& key, const Value& value);                                                     // Replaces a certain key with a different value
  void clear();                                                                                         // Clears the tree

  // Utility
  void in_order();                                                                                      // Prints the list (in-order)
  void pre_order();                                                                                     // Prints the list (pre-order)
  void post_order();                                                                                    // Prints the list (post-order)
  
  // Iterator
  class Iterator {
  private:
    AVLTreeNode<Key, Value>* current;
    public:
    // Constructor
    Iterator(AVLTreeNode<Key, Value>* node) : current(node) { }
    
    // Dereference methods
    const Value& value() const { return current->value; }
    const Key& key() const { return current->key; }
    
    // Get the current node
    AVLTreeNode<Key, Value>* get_node() { return current; }
    
    // Increment methods
    Iterator& right() { current = current->right; return *this; }
    Iterator& left() { current = current->left; return *this; }

    // Inequality operator
    bool operator!=(const Iterator& other) const { return current != other.current; }
  };

  // Iterator methods
  Iterator begin() { return Iterator(root); }               // Returns an iterator pointing to the root node
  Iterator end() { return Iterator(nullptr); }              // Returns an iterator pointing to the end (nullptr)
  const Iterator begin() const { return Iterator(root); }   // Returns a const iterator pointing to the root node
  const Iterator end() const { return Iterator(nullptr); }  // Returns a const iterator pointing to the end (nullptr)

};

// Function Definitions
template <typename Key, typename Value>
AVLTree<Key, Value>::~AVLTree() {
  clear();
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::search(AVLTreeNode<Key, Value>* node, const Key& key) {
  if (node == nullptr) throw std::out_of_range("Key not found");

  if (key < node->key) return search(node->left, key);
  if (key > node->key) return search(node->right, key);

  return node;
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::search(AVLTreeNode<Key, Value>* node, const Key& key) const {
  if (node == nullptr) throw std::out_of_range("Key not found");

  if (key < node->key) return search(node->left, key);
  if (key > node->key) return search(node->right, key);

  return node;
}

template <typename Key, typename Value>
const AVLTreeNode<Key, Value>* AVLTree<Key, Value>::contains(AVLTreeNode<Key, Value>* node, const Key& key) const {
  if (node == nullptr) return nullptr;

  if (key < node->key) return contains(node->left, key);
  if (key > node->key) return contains(node->right, key);

  return node;
}

template <typename Key, typename Value>
const int AVLTree<Key, Value>::get_height(AVLTreeNode<Key, Value>* node) const {
  if (node == nullptr) return 0;

  return node->height;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::update_height(AVLTreeNode<Key, Value>* node) {
  if (node == nullptr) return;

  node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}

template <typename Key, typename Value>
const int AVLTree<Key, Value>::get_balance(AVLTreeNode<Key, Value>* node) const {
  if (node == nullptr) return 0;

  return get_height(node->left) - get_height(node->right);
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::rotate_left(AVLTreeNode<Key, Value>* x) {
  AVLTreeNode<Key, Value>* y = x->right;
  AVLTreeNode<Key, Value>* T2 = y->left;

  y->left = x;
  x->right = T2;

  update_height(x);
  update_height(y);

  return y;
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::rotate_right(AVLTreeNode<Key, Value>* y) {
  AVLTreeNode<Key, Value>* x = y->left;
  AVLTreeNode<Key, Value>* T2 = x->right;

  x->right = y;
  y->left = T2;

  update_height(x);
  update_height(y);

  return x;
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::insert(AVLTreeNode<Key, Value>* node, const Key& key, const Value& value) {
  if (node == nullptr) { 
    tree_size++;
    return new AVLTreeNode<Key, Value>(key, value); 
    }

  if (key < node->key) {
    node->left = insert(node->left, key, value);
  }
  else if (key > node->key) {
    node->right = insert(node->right, key, value);
  }
  else {
    return node;
  }

  update_height(node);

  int balance = get_balance(node);

  // right
  if (balance > 1 && key < node->left->key) {
    return rotate_right(node);
  }

  // left
  if (balance < -1 && key > node->right->key) { 
    return rotate_left(node);
  }

  // left-right
  if (balance > 1 && key > node->left->key) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
  }

  // right-left
  if (balance < -1 && key < node->right->key) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }

  return node;
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::remove(AVLTreeNode<Key, Value>* node, const Key& key) {
  if (node == nullptr) return nullptr;

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  }
  else {
    tree_size--;

    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;

    } else if (node->left == nullptr) {
      AVLTreeNode<Key, Value>* temp = node;
      node = node->right;
      delete temp;
    
    } else if (node->right == nullptr) {
      AVLTreeNode<Key, Value>* temp = node;
      node = node->left;
      delete temp;

    }else {
      AVLTreeNode<Key, Value>* temp = get_local_min(node->right);
      node->key = temp->key;
      node->value = temp->value;
      node->right = remove(node->right, temp->key);
    }
  }

  if (node == nullptr) return node;

  update_height(node);

  int balance = get_balance(node);

  // right
  if (balance > 1 && get_balance(node->left) >= 0) {
    return rotate_right(node);
  }
  
  // left
  if (balance < -1 && get_balance(node->right) >= 0) {
    return rotate_left(node);
  }

  // left-right
  if (balance > 1 && get_balance(node->left) < 0) {
    node->left = rotate_left(node->left);
    return rotate_right(node);
  }

  // right-left
  if (balance < -1 && get_balance(node->right) > 0) {
    node->right = rotate_right(node->right);
    return rotate_left(node);
  }

  return node;
}

template <typename Key, typename Value>
AVLTreeNode<Key, Value>* AVLTree<Key, Value>::get_local_min(AVLTreeNode<Key, Value>* node) {
  AVLTreeNode<Key, Value>* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear(AVLTreeNode<Key, Value>* node) {
  if (node == nullptr) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::print_node(AVLTreeNode<Key, Value>* node) {
  std::cout << "(" << node->key << "," << node->value << "), ";
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::in_order(AVLTreeNode<Key, Value>* node) {
  if (node == nullptr) return;

  in_order(node->left);
  print_node(node);
  in_order(node->right);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::pre_order(AVLTreeNode<Key, Value>* node) {
  if (node == nullptr) return;

  print_node(node);
  pre_order(node->left);
  pre_order(node->right);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::post_order(AVLTreeNode<Key, Value>* node) {
  if (node == nullptr) return;

  post_order(node->left);
  post_order(node->right);
  print_node(node);
}

template <typename Key, typename Value>
Value& AVLTree<Key, Value>::search(const Key& key) {
  return search(root, key)->value;
}

template <typename Key, typename Value>
const Value& AVLTree<Key, Value>::search(const Key& key) const {
  return search(root, key)->value;
}

template <typename Key, typename Value>
const bool AVLTree<Key, Value>::contains(const Key& key) const {
  return contains(root, key) != nullptr;
}

template <typename Key, typename Value>
const bool AVLTree<Key, Value>::empty() const {
  return root == nullptr;
}

template <typename Key, typename Value>
const int AVLTree<Key, Value>::size() const {
  return tree_size;
}

template <typename Key, typename Value>
const int AVLTree<Key, Value>::height() const {
  if (root == nullptr) return 0;

  return root->height;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::insert(const Key& key, const Value& value) {
  root = insert(root, key, value);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key) {
  remove(root, key);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::replace(const Key& key, const Value& value) {
  AVLTreeNode<Key, Value>* node = search(root, key);
  node->value = value;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::clear() {
  clear(root);
  root = nullptr;
  tree_size = 0;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::in_order() {
  in_order(root);
  std::cout << std::endl;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::pre_order() {
  pre_order(root);
  std::cout << std::endl;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::post_order() {
  post_order(root);
  std::cout << std::endl;
}

#endif
