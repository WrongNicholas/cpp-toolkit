// LinkedList.hpp
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include <iostream>

// Struct defining a node in linked list
template <typename Value>
struct ListNode {
  Value value;      // Value stored in the node
  ListNode* next;   // Pointer to the next node in the list
  
  // Constructor to initialize the node with a value
  ListNode(Value value) : value(value), next(nullptr) {}
};

// Class representing singly linked list
template <typename Value>
class LinkedList {
private:
  ListNode<Value>* head;    // Pointer to the first node in the list
  ListNode<Value>* tail;    // Pointer to the last node in the list

  // Private helper function to get node at a specific index
  ListNode<Value>* get_node_at(int index) const;

public:                                    
  // Constructors and Destructor           
  LinkedList() : head(nullptr), tail(nullptr) {}            // Default constructor
  LinkedList(const LinkedList<Value> &other);                   // Copy constructor
  ~LinkedList();                                            // Destructor
   
  // Accessors
  Value& operator[](int index);                                 // Overloaded subscript operator
  const Value& operator[](int index) const;                     // Overloaded const subscript operator
  Value& front();                                               // Returns value at the front of the list
  const Value& front() const;                                   // Returns value at the front of the list (const)
  Value& back();                                                // Returns value at the back of the list
  const Value& back() const;                                    // Returns value at the back of the list (const)
  int size() const;                                         // Returns the number of elements in the list
  bool empty() const;                                       // Checks if the list empty

  // Mutators
  void push_front(const Value& value);                          // Adds a new element at the front of the list
  void push_back(const Value& value);                           // Adds a new element at the back of the list
  void insert(int index, const Value& value);                   // Adds a new element at the specified index
  void remove_all(const Value& value);                          // Removes all occurances of a value from the list
  void remove_at(int index);                                // Removes the element at specified index
  void pop_front();                                         // Removes the element at the front of the list
  void pop_back();                                          // Removes the element at the back of the list
  void clear();                                             // Removes all elements from the list

  // Utility
  int find(const Value& value) const;                           // Finds the index of the first occurance of a value
  bool contains(const Value& value) const;                      // Checks if the list contains a specific value
  void print();                                             // Prints all elements in the list

  // Iterator
  class Iterator {
  private:
    ListNode<Value>* current;   // Pointer to the current node in the iteration
  public:
    // Constructor
    Iterator(ListNode<Value>* node) : current(node) { }

    // Dereference operator
    Value& operator*() const { return current->value; }

    // Get the current node
    ListNode<Value>* get_node() { return current; }

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

template <typename Value>
ListNode<Value>* LinkedList<Value>::get_node_at(int index) const {
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

template <typename Value>
LinkedList<Value>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
  if (other.head == nullptr) {
    return;
  }
  
  this->head = new ListNode<Value>(other.head->value);
  ListNode<Value>* current = this->head;
  ListNode<Value>* temp = other.head->next;

  while (temp != nullptr) {
    current->next = new ListNode<Value>(temp->value);
    current = current->next;
    temp = temp->next;
  }

  this->tail = current;
}

template <typename Value>
LinkedList<Value>::~LinkedList() {
  clear();
} 

template <typename Value>
Value& LinkedList<Value>::operator[](int index) {
  return get_node_at(index)->value;
}

template <typename Value>
const Value& LinkedList<Value>::operator[](int index) const {
  return get_node_at(index)->value;
}

template <typename Value>
Value& LinkedList<Value>::front() {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->head->value;
}

template <typename Value>
const Value& LinkedList<Value>::front() const {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->head->value;
}

template <typename Value>
Value& LinkedList<Value>::back() {
  if (this->tail == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->tail->value;
}

template <typename Value>
const Value& LinkedList<Value>::back() const {
  if (this->tail == nullptr) {
    throw std::out_of_range("List is empty");
  }

  return this->tail->value;
}

template <typename Value>
int LinkedList<Value>::size() const {
  int count = 0;
  for (auto element = begin(); element != end(); ++element, ++count);
  return count;
}

template <typename Value>
bool LinkedList<Value>::empty() const {
  return this->head == nullptr;
}

template <typename Value>
void LinkedList<Value>::push_front(const Value& value) {
  ListNode<Value>* node = new ListNode<Value>(value);
  
  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
    return;
  }
  
  node->next = this->head;
  this->head = node;
}

template <typename Value>
void LinkedList<Value>::push_back(const Value& value) {
  ListNode<Value>* node = new ListNode<Value>(value);
  
  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
    return;
  }
  
  this->tail->next = node;
  this->tail = node;
}

template <typename Value>
void LinkedList<Value>::insert(int index, const Value& value) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }

  if (index == 0) {
    this->push_front(value);
    return;
  }

  ListNode<Value>* current = get_node_at(index - 1);
  
  ListNode<Value>* node = new ListNode<Value>(value);

  node->next = current->next;
  current->next = node;

  if (node->next == nullptr) {
    this->tail = node;
  }
}

template <typename Value>
void LinkedList<Value>::remove_all(const Value& value) {
  ListNode<Value>* current = this->head;
  ListNode<Value>* previous = nullptr;

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
      ListNode<Value>* temp = current;
      current = current->next;
      delete temp;
    }
    else {
      previous = current;
      current = current->next;
    }
  }
}

template <typename Value>
void LinkedList<Value>::remove_at(int index) {
  if (index < 0 || index >= this->size()) {
    throw std::out_of_range("Index out of range");
  }

  if (index == 0) {
    pop_front();
    return;
  }

  ListNode<Value>* previous = get_node_at(index - 1);

  ListNode<Value>* temp = previous->next;
  previous->next = temp->next;

  if (temp == tail) {
    tail = previous;
  }
  
  delete temp;
}

template <typename Value>
void LinkedList<Value>::pop_front() {
  if (this->head == nullptr) {
    return;
  }
  
  ListNode<Value>* temp = this->head;
  this->head = this->head->next;
  
  if (this->head == nullptr) {
    this->tail = nullptr;
  }

  delete temp;
}

template <typename Value>
void LinkedList<Value>::pop_back() {
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  if (this->head->next == nullptr) {
    delete this->head;
    this->head = nullptr;
    this->tail = nullptr;
    return;
  }
  
  ListNode<Value>* current = this->head;
  while (current->next != this->tail) {
    current = current->next;
  }

  delete this->tail;
  this->tail = current;
  this->tail->next = nullptr;
}

template <typename Value>
void LinkedList<Value>::clear() {
  ListNode<Value>* current = this->head;
  while (current != nullptr) {
    ListNode<Value>* next = current->next;
    delete current;
    current = next;
  }

  this->head = nullptr;
  this->tail = nullptr;
}

template <typename Value>
int LinkedList<Value>::find(const Value& value) const {
  int count = 0;
  for (auto element = begin(); element != end(); ++element, ++count) {
    if (*element == value) {
      return count;
    }
  }

  throw std::runtime_error("Value not found");
}

template <typename Value>
bool LinkedList<Value>::contains(const Value& value) const {

  for (auto element = begin(); element != end(); ++element) {
    if (*element == value) {
      return true;
    }
  }

  return false;
}

template <typename Value>
void LinkedList<Value>::print() {
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
