// LinkedList.hpp
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <iostream>

// Struct defining a node in linked list
template <typename T>
struct ListNode {
  T value;          // Value stored in the node
  ListNode* next;   // Pointer to the next node in the list
  
  // Constructor to initialize the node with a value
  ListNode(T value) : value(value), next(nullptr) {}
};

// Class representing singly linked list
template <typename T>
class LinkedList {
private:
  ListNode<T>* head;        // Pointer to the first node in the list
  ListNode<T>* tail;        // Pointer to the last node in the list
  size_t list_size;         // Size of the linked list

  // Private helper function to get node at a specific index
  const ListNode<T>* get_node_at(int index) const;
  ListNode<T>* get_node_at(int index);

public:                                    
  // Constructors and Destructor           
  LinkedList() : head(nullptr), tail(nullptr), list_size(0) {}  // Default constructor
  LinkedList(const LinkedList<T> &other);                       // Copy constructor
  ~LinkedList();                                                // Destructor
   
  // Accessors
  T& operator[](int index);                                     // Overloaded subscript operator
  const T& operator[](int index) const;                         // Overloaded const subscript operator
  T& front();                                                   // Returns value at the front of the list
  const T& front() const;                                       // Returns value at the front of the list (const)
  T& back();                                                    // Returns value at the back of the list
  const T& back() const;                                        // Returns value at the back of the list (const)
  const size_t size() const;                                    // Returns the number of elements in the list
  const bool empty() const;                                     // Checks if the list empty

  // Mutators
  void push_front(const T& value);                              // Adds a new element at the front of the list
  void push_back(const T& value);                               // Adds a new element at the back of the list
  void insert(int index, const T& value);                       // Adds a new element at the specified index
  void remove_all(const T& value);                              // Removes all occurances of a value from the list
  void remove_at(int index);                                    // Removes the element at specified index
  void pop_front();                                             // Removes the element at the front of the list
  void pop_back();                                              // Removes the element at the back of the list
  void clear();                                                 // Removes all elements from the list

  // Utility
  const int find(const T& value) const;                         // Finds the index of the first occurance of a value
  const bool contains(const T& value) const;                    // Checks if the list contains a specific value
  void print();                                                 // Prints all elements in the list

  // Iterator
  class Iterator {
  private:
    ListNode<T>* current;   // Pointer to the current node in the iteration
  public:
    // Constructor
    Iterator(ListNode<T>* node) : current(node) { }

    // Dereference operator
    T& operator*() const { return current->value; }

    // Get the current node
    ListNode<T>* get_node() { return current; }

    // Increment operator
    Iterator& operator++() { current = current->next; return *this; }

    // Inequality operator
    bool operator!=(const Iterator& other) const { return current != other.current; }
  };

  // Iterator methods
  Iterator begin() { return Iterator(head); }         // Returns an iterator pointing to the first element
  Iterator end() { return Iterator(nullptr); }        // Retrns an iterator pointing to the end (nullptr)
  Iterator begin() const { return Iterator(head); }   // Returns a const iterator pointing to the first element
  Iterator end() const { return Iterator(nullptr); }  // Returns a const iterator pointing to the end (nullptr)
};

// Function Definitions
template <typename T>
const ListNode<T>* LinkedList<T>::get_node_at(int index) const {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  
  int count = 0;
  for (auto node = begin(); node != end(); ++node, ++count) {
    if (count == index) {
      return node.get_node();
    }
  }

  throw std::out_of_range("Index out of range");
}

template <typename T>
ListNode<T>* LinkedList<T>::get_node_at(int index){
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  
  int count = 0;
  for (auto node = begin(); node != end(); ++node, ++count) {
    if (count == index) {
      return node.get_node();
    }
  }
  throw std::out_of_range("Index out of range");
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
  if (other.head == nullptr) {
    return;
  }
  
  this->head = new ListNode<T>(other.head->value);
  ListNode<T>* current = this->head;
  ListNode<T>* temp = other.head->next;

  while (temp != nullptr) {
    current->next = new ListNode<T>(temp->value);
    current = current->next;
    temp = temp->next;
  }

  this->tail = current;
  this->size = other.size;
}

template <typename T>
LinkedList<T>::~LinkedList() {
  clear();
} 

template <typename T>
T& LinkedList<T>::operator[](int index) {
  return get_node_at(index)->value;
}

template <typename T>
const T& LinkedList<T>::operator[](int index) const {
  return get_node_at(index)->value;
}

template <typename T>
T& LinkedList<T>::front() {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->head->value;
}

template <typename T>
const T& LinkedList<T>::front() const {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->head->value;
}

template <typename T>
T& LinkedList<T>::back() {
  if (this->tail == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->tail->value;
}

template <typename T>
const T& LinkedList<T>::back() const {
  if (this->tail == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->tail->value;
}

template <typename T>
const size_t LinkedList<T>::size() const {
  return list_size;
}

template <typename T>
const bool LinkedList<T>::empty() const {
  return this->head == nullptr;
}

template <typename T>
void LinkedList<T>::push_front(const T& value) {
  list_size++;
  ListNode<T>* node = new ListNode<T>(value);
  
  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
    return;
  }
  
  node->next = this->head;
  this->head = node;
}

template <typename T>
void LinkedList<T>::push_back(const T& value) {
  list_size++;
  ListNode<T>* node = new ListNode<T>(value);
  
  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
    return;
  }
  
  this->tail->next = node;
  this->tail = node;
}

template <typename T>
void LinkedList<T>::insert(int index, const T& value) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }

  list_size++;
  if (index == 0) {
    this->push_front(value);
    return;
  }

  ListNode<T>* current = get_node_at(index - 1);
  
  ListNode<T>* node = new ListNode<T>(value);

  node->next = current->next;
  current->next = node;

  if (node->next == nullptr) {
    this->tail = node;
  }
}

template <typename T>
void LinkedList<T>::remove_all(const T& value) {
  ListNode<T>* current = this->head;
  ListNode<T>* previous = nullptr;

  while (current != nullptr) {
    if (current->value == value) {
      if (current == this->head) {
        this->head = current->next;
      }

      if (current == tail) {
        this->tail = previous; 
      }

      if (previous != nullptr) {
        previous->next = current->next;
      } 
      ListNode<T>* temp = current;
      current = current->next;
      delete temp;

      list_size--;
    }
    else {
      previous = current;
      current = current->next;
    }
  }
}

template <typename T>
void LinkedList<T>::remove_at(int index) {
  if (index < 0 || index >= this->size()) {
    throw std::out_of_range("Index out of range");
  }

  list_size--;
  if (index == 0) {
    pop_front();
    return;
  }

  ListNode<T>* previous = get_node_at(index - 1);

  ListNode<T>* temp = previous->next;
  previous->next = temp->next;

  if (temp == tail) {
    tail = previous;
  }
  
  delete temp;
}

template <typename T>
void LinkedList<T>::pop_front() {
  if (this->head == nullptr) {
    return;
  }
  
  ListNode<T>* temp = this->head;
  this->head = this->head->next;
  
  if (this->head == nullptr) {
    this->tail = nullptr;
  }

  delete temp;
  list_size--;
}

template <typename T>
void LinkedList<T>::pop_back() {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  list_size--;
  if (this->head->next == nullptr) {
    delete this->head;
    this->head = nullptr;
    this->tail = nullptr;
    return;
  }
  
  ListNode<T>* current = this->head;
  while (current->next != this->tail) {
    current = current->next;
  }

  delete this->tail;
  this->tail = current;
  this->tail->next = nullptr;
}

template <typename T>
void LinkedList<T>::clear() {
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
const int LinkedList<T>::find(const T& value) const {
  int count = 0;
  for (auto element = begin(); element != end(); ++element, ++count) {
    if (*element == value) {
      return count;
    }
  }

  throw std::runtime_error("T not found");
}

template <typename T>
const bool LinkedList<T>::contains(const T& value) const {

  for (auto element = begin(); element != end(); ++element) {
    if (*element == value) {
      return true;
    }
  }

  return false;
}

template <typename T>
void LinkedList<T>::print() {
  if (this->head == nullptr) {
    std::cout << "Ø" << std::endl;
    return;
  }
  
  for (auto element = begin(); element != end(); ++element) {
    std::cout << *element << " ";
  }

  std::cout << std::endl;
}

#endif
