#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdexcept>
#include <iostream>

// Struct defining a node in doubly linked list
template <typename T>
struct ListNode {
  T value;          // Value stored in the node
  ListNode* next;   // Pointer to the next node in the list
  ListNode* prev;   // Pointer to the previous node in the list

  // Constructor to initialize the node with a value
  ListNode(T value) : value(value), next(nullptr), prev(nullptr) {}
};

// Class representing a doubly linked list
template <typename T>
class DoublyLinkedList {
private:
  ListNode<T>* head;
  ListNode<T>* tail;
  size_t list_size;

  // Private helper function to get node at a specific index
  ListNode<T>* get_node_at(int);
  const ListNode<T>* get_node_at(int) const;
public:
  // Constructors and Destructor
  DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}
  ~DoublyLinkedList();

  // Accessors
  T& operator[](int);
  const T& operator[](int) const;

  // Mutators
  void push_front(const T&);
  void push_back(const T&);
  void insert(int, const T&);
  void remove_all(const T&);
  void remove_at(int);
  void pop_front();
  void pop_back();
  void clear();

  // Utility
  void print();
  void print_reverse();

  class Iterator {
  private:
    ListNode<T>* current;
  public:
    // Constructor
    Iterator(ListNode<T>* node) : current(node) { }

    // Dereference operator
    T& operator*() const { return current->value; }

    // Get the current node
    ListNode<T>* get_node() { return current; }

    // Increment operator
    Iterator& operator++() { current = current->next; return *this; }

    // Decrement operator
    Iterator& operator--() { current = current->prev; return *this; }

    // Inequality operator
    bool operator!=(const Iterator& other) const { return current != other.current; }
  };

  // Iterator methods
  Iterator begin_head() { return Iterator(head); }
  const Iterator begin_head() const { return Iterator(head); }
  Iterator begin_tail() { return Iterator(tail); }
  const Iterator begin_tail() const { return Iterator(tail); }
  Iterator end() { return Iterator(nullptr); }
  const Iterator end() const { return Iterator(nullptr); }
};

// Function Definitions
template <typename T>
ListNode<T>* DoublyLinkedList<T>::get_node_at(int index) {
  if (index < 0 || index >= list_size) {
    throw std::out_of_range("Index out of range");
  }

  if (list_size - index < list_size/2) {
    int count = 0;
    for (auto node = begin_head(); node != end(); ++node, ++count) {
      if (count == index)
        return node.get_node();
    }
  } else {
    int count = list_size - 1;
    for (auto node = begin_tail(); node != end(); --node, --count) {
      if (count == index)
        return node.get_node();
    }
  }

  throw std::out_of_range("Index out of range");
}

template <typename T>
const ListNode<T>* DoublyLinkedList<T>::get_node_at(int index) const {
  if (index < 0 || index >= list_size) {
    throw std::out_of_range("Index out of range");
  }

  if (list_size - index < list_size/2) {
    int count = 0;
    for (auto node = begin_head(); node != end(); ++node, ++count) {
      if (count == index)
        return node.get_node();
    }
  } else {
    int count = list_size - 1;
    for (auto node = begin_tail(); node != end(); --node, --count) {
      if (count == index)
        return node.get_node();
    }
  }

  throw std::out_of_range("Index out of range");
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
  return this->get_node_at(index)->value; 
}

template <typename T>
const T& DoublyLinkedList<T>::operator[](int index) const {
  return this->get_node_at(index)->value;
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
  list_size++;
  ListNode<T>* node = new ListNode<T>(value);

  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
    return;
  }

  this->head->prev = node;
  node->next = this->head;
  this->head = node;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
  list_size++;
  ListNode<T>* node = new ListNode<T>(value);

  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
    return;
  }
  
  node->prev = this->tail;
  this->tail->next = node;
  this->tail = node;
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, const T& value) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }

  list_size++;
  if (index == 0) {
    this->push_front(value);
    return;
  }

  ListNode<T>* current = get_node_at(index);
  ListNode<T>* node = new ListNode<T>(value);

  node->next = current->next;
  node->next->prev = node;

  current->next = node;
  node->prev = current;

  if (node->next == nullptr) {
    this->tail = node;
  }
}

template <typename T>
void DoublyLinkedList<T>::remove_all(const T& value) {
  ListNode<T>* current = this->head;
  ListNode<T>* prev = nullptr;

  while (current != nullptr) {
    if (current->value != value) {
      prev = current;
      current = current->next;
      continue;
    }

    if (current == this->head) {
      this->head = current->next;
      if (this->head != nullptr) this->head->prev = nullptr;
    }

    if (current == this->tail) {
      this->tail = prev;
      if (this->tail != nullptr) this->tail->next = nullptr;
    }

    if (prev != nullptr) prev->next = current->next;

    ListNode<T>* delete_me = current;
    current = current->next;
    delete delete_me;

    this->list_size--;

    if (this->head == nullptr) this->tail = nullptr;
  }
}

template <typename T>
void DoublyLinkedList<T>::remove_at(int index) {

}

template <typename T>
void DoublyLinkedList<T>::pop_front() {

}

template <typename T>
void DoublyLinkedList<T>::pop_back() {

}

template <typename T>
void DoublyLinkedList<T>::clear() {
  ListNode<T>* current = this->head;
  while (current != nullptr) {
    ListNode<T>* next = current->next;
    delete current;
    current = next;
  }

  this->head = nullptr;
  this->tail = nullptr;
  list_size = 0;
}

template <typename T>
void DoublyLinkedList<T>::print() {
  if (this->head == nullptr) {
    std::cout << "Ø" << std::endl;
    return;
  }

  for (auto element = begin_head(); element != end(); ++element) {
    std::cout << *element << " ";
  }

  std::cout << std::endl;
}

template <typename T>
void DoublyLinkedList<T>::print_reverse() {
  if (this->tail == nullptr) {
    std::cout << "Ø" << std::endl;
    return;
  }

  for (auto element = begin_tail(); element != end(); --element) {
    std::cout << *element << " ";
  }

  std::cout <<std::endl;
}

#endif
