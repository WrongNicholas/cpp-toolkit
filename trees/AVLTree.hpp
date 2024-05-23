#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <stdexcept>

template <typename Key, typename Value>
struct Node {
  Key key;
  Value value;
  int height;

  Node<Key, Value>* left;
  Node<Key, Value>* right;

  Node(const Key& key, const Value& value) : key(key), value(value), height(0), left(nullptr), right(nullptr) {}
};

template <typename Key, typename Value>
class AVLTree {
private:
  Node<Key, Value>* root;

  // Helper Functions
  Node<Key, Value>* search(Node<Key, Value>* node, const Key& key);
  Node<Key, Value>* search(Node<Key, Value>* node, const Key& key) const;

  int get_height(Node<Key, Value>* node) const;
  void update_height(Node<Key, Value>* node);
  int get_balance(Node<Key, Value>* node) const;

  Node<Key, Value>* rotate_left(Node<Key, Value>* x);
  Node<Key, Value>* rotate_right(Node<Key, Value>* y);
  Node<Key, Value>* insert(Node<Key, Value>* node, const Key& key, const Value& value); 

  Node<Key, Value>* remove(Node<Key, Value>* node, const Key& key);
  Node<Key, Value>* get_local_min(Node<Key, Value>* node);

  // Utility
  void print_node(Node<Key, Value>* node);
  void in_order(Node<Key, Value>* node);
  void pre_order(Node<Key, Value>* node);
  void post_order(Node<Key, Value>* node);
public:
  AVLTree() : root(nullptr) {}
  
  // Accessors
  Value& search(const Key& key);
  Value& search(const Key& key) const;

  // Mutators
  void insert(const Key& key, const Value& value);
  void remove(const Key& key);

  // Utility
  void in_order();
  void pre_order();
  void post_order();
};

// Function Definitions
template <typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::search(Node<Key, Value>* node, const Key& key) {
  if (node == nullptr) throw std::out_of_range("Key not found");

  if (key < node->key) return search(node->left, key);
  if (key > node->key) return search(node->right, key);

  return node;
}

template <typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::search(Node<Key, Value>* node, const Key& key) const {
  if (node == nullptr) throw std::out_of_range("Key not found");

  if (key < node->key) return search(node->left, key);
  if (key > node->key) return search(node->right, key);

  return node;
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::get_height(Node<Key, Value>* node) const {
  if (node == nullptr) return 0;

  return node->height;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::update_height(Node<Key, Value>* node) {
  if (node == nullptr) return;

  node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
}

template <typename Key, typename Value>
int AVLTree<Key, Value>::get_balance(Node<Key, Value>* node) const {
  if (node == nullptr) return 0;

  return get_height(node->left) - get_height(node->right);
}

template <typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::rotate_left(Node<Key, Value>* x) {
  Node<Key, Value>* y = x->right;
  Node<Key, Value>* T2 = y->left;

  y->left = x;
  x->right = T2;

  update_height(x);
  update_height(y);

  return y;
}

template <typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::rotate_right(Node<Key, Value>* y) {
  Node<Key, Value>* x = y->left;
  Node<Key, Value>* T2 = x->right;

  x->right = y;
  y->left = T2;

  update_height(x);
  update_height(y);

  return x;
}

template <typename Key, typename Value>
Node<Key, Value>* AVLTree<Key, Value>::insert(Node<Key, Value>* node, const Key& key, const Value& value) {
  if (node == nullptr) return new Node<Key, Value>(key, value);

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
Node<Key, Value>* AVLTree<Key, Value>::remove(Node<Key, Value>* node, const Key& key) {
  if (node == nullptr) return node;

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  }
  else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;

    } else if (node->left == nullptr) {
      Node<Key, Value>* temp = node;
      node = node->right;
      delete temp;
    
    } else if (node->right == nullptr) {
      Node<Key, Value>* temp = node;
      node = node->left;
      delete temp;

    }else {
      Node<Key, Value>* temp = get_local_min(node->right);
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
Node<Key, Value>* AVLTree<Key, Value>::get_local_min(Node<Key, Value>* node) {
  Node<Key, Value>* current = node;
  while (current->left != nullptr) {
    current = current->left;
  }
  return current;
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::print_node(Node<Key, Value>* node) {
  std::cout << "(" << node->key << "," << node->value << "), ";
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::in_order(Node<Key, Value>* node) {
  if (node == nullptr) return;

  in_order(node->left);
  print_node(node);
  in_order(node->right);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::pre_order(Node<Key, Value>* node) {
  if (node == nullptr) return;

  print_node(node);
  pre_order(node->left);
  pre_order(node->right);
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::post_order(Node<Key, Value>* node) {
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
Value& AVLTree<Key, Value>::search(const Key& key) const {
  return search(root, key)->value;
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
