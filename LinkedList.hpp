#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Struct defining a node in linked list
template <typename T>
struct ListNode {
  T value;
  ListNode* next;
  
  ListNode(T value) : value(value), next(nullptr) {}
};

// Class representing singly linked list
template <typename T>
class LinkedList {
private:
  ListNode<T>* head;                          // Pointer to first node in list 
public:                                    
  // Constructors and Destructor           
  LinkedList<T>();                            // Default constructor
  LinkedList<T>(const LinkedList<T> &other);     // Copy constructor
  ~LinkedList<T>();                           // Destructor

  // Accessors
  T& value_at(int index);                 // Returns value stored at specific index
  T& front();                             // Returns value at list head
  T& back();                              // Returns value at list tail
  T& operator[](int index);              // Overloaded subscript operator

  int size() const;                        // Returns number of elements
  bool empty() const;                      // Checks if list empty

  // Mutators
  void push_front(const T& value);              // Adds new element at head
  void push_back(const T& value);               // Adds new element at tail
  void insert(int index, const T& value);       // Adds new element at specified index
  
  void remove_all(const T& value);              // Removes all elements of value
  void pop_front();                        // Removes head element
  void pop_back();                         // Removes tail element
  void clear();                            // Removes all elements

  // Utility
  int find(const T& value) const;               // Finds index of first occurance of value
  void print_list();                       // Prints all elements
};

#include <stdexcept>

// Return value at index
template <typename T>
T& LinkedList<T>::value_at(int index) {
  // Check if index is within lower range
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  
  // Traverse list until reaching index
  int i = 0;
  ListNode<T>* current = this->head;
  while (current != nullptr) {

    // Return value if current node matches index
    if (i == index) {
      return current->value;
    }
    
    // Move to next node and increment local index
    current = current->next;
    i++;
  }
  
  // Throw exception if selected index out of range
  throw std::out_of_range("Index out of range");
}

// Return value at front of list
template <typename T>
T& LinkedList<T>::front() {
  // Check if list is empty
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  // Return head node
  return this->head->value;
}

// Return value at back of list
template <typename T>
T& LinkedList<T>::back() {
  // Check if list is empty
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  // Traverse list until current node is tail
  ListNode<T>* current = this->head;
  while (current->next != nullptr) {
    current = current->next;
  }
  
  // Return tail node
  return current->value;
}

// Overload subscript operator
template <typename T>
T& LinkedList<T>::operator[](int index) {
  // Check if index is within lower range
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  
  // Traverse list until current node matches index
  int i = 0;
  ListNode<T>* current = this->head;
  while (current != nullptr) {
    // Return value if current node matches index 
    if (i == index) {
      return current->value;
    }
    
    // Move to next node and increment local index
    current = current->next;
    i++;
  }

  // Throw exception if selected index out of range
  throw std::out_of_range("Index out of range");
}

// Return number of elements
template <typename T>
int LinkedList<T>::size() const {
  
  // Traverse list until tail
  int i = 0;
  ListNode<T>* current = this->head;
  while (current != nullptr) {
    current = current->next;
    i++;
  }

  // Return size
  return i;
}

template <typename T>
bool LinkedList<T>::empty() const {
  return this->head == nullptr;
}

// Add new element to front of list
template <typename T>
void LinkedList<T>::push_front(const T& value) {
  // Make new node with provided value 
  ListNode<T>* node = new ListNode(value);
  
  // Give value to head if list empty
  if (this->head == nullptr) {
    this->head = node;

    // Return because I'm a never-nester (shout out CodeAesthetic)
    return;
  }
  
  // Shift previous head
  node->next = this->head;
  this->head = node;
}

// Add new element to end of list
template <typename T>
void LinkedList<T>::push_back(const T& value) {
  // Initialize ListNode
  ListNode<T>* node = new ListNode(value);

  // Check if list empty
  if (this->head == nullptr) {
    this->head = node;
    return;
  }

  // Traverse list to find tail
  ListNode<T>* temp = this->head;
  while(temp->next != nullptr) {
    temp = temp->next;
  }
  
  // Set tail's next to new node
  temp->next = node;
}

// Add new element at index
template <typename T>
void LinkedList<T>::insert(int index, const T& value) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }

  // Call push_front if index is 0
  if (index == 0) {
    this->push_front(value);
    return;
  }

  // Traverse list until desired index - 1
  ListNode<T>* current = this->head;
  for (int i = 1; i < index; i++) {
    // Check if in bounds
    if (current == nullptr) {
      throw std::out_of_range("Index out of range");
    }
    
    // Move to next node
    current = current->next;
  }
  
  // Insert node between current and current's next
  ListNode<T>* node = new ListNode(value);
  node->next = current->next;
  current->next = node;
}

// Remove all element(s) of value from list
template <typename T>
void LinkedList<T>::remove_all(const T& value) {
  // Check if list empty
  if (this->head == nullptr) {
    return;
  }

  // Remove head node(s) of value
  while(this->head != nullptr && this->head->value == value) {
    ListNode<T>* temp = this->head;
    this->head = this->head->next;
    delete temp;
  }

  // Check if list is empty after removing head node(s)
  if (this->head == nullptr) {
    return;
  }
  
  // Remove all remaining non-head nodes of value
  ListNode<T>* current = this->head;
  while (current->next != nullptr) {
    // Remove current's next if matches value
    if (current->next->value == value) {
      ListNode<T>* temp = current->next;
      current->next = current->next->next;
      delete temp;
      
    } else {
      // Move to next node
      current = current->next;
    }
  }
}

// Remove element at front of list
template <typename T>
void LinkedList<T>::pop_front() {
  // Check if list empty
  if (this->head == nullptr) {
    return;
  }
  
  // Remove first node
  ListNode<T>* temp = this->head;
  this->head = this->head->next;
  delete temp;
}

// Remove element at end of list
template <typename T>
void LinkedList<T>::pop_back() {
  // Check if list empty
  if (this->head == nullptr) {
    return;
  }

  // Remove head and return if list is singleton
  if (this->head->next == nullptr) {
    delete this->head;
    this->head = nullptr;
    return;
  }
  
  // Traverse list until reaching second to tail
  ListNode<T>* temp = this->head;
  while (temp->next->next != nullptr) {
    temp = temp->next;
  }

  // Remove tail
  delete temp->next;
  temp->next = nullptr;
}

// Clear list
template <typename T>
void LinkedList<T>::clear() {
  // Traverse list and delete  nodes
  ListNode<T>* current = this->head;
  while (current != nullptr) {
    ListNode<T>* next = current->next;
    delete current;
    current = next;
  }

  // Reset head pointer
  this->head = nullptr;
}

// Find index of first occurance of value
template <typename T>
int LinkedList<T>::find(const T& value) const {
  // Traverse until desired value found
  ListNode<T>* current = this->head;
  int i = 0;
  while (current != nullptr) {
    if (current->value == value) {
      return i;
    }
    current = current->next;
    i++;
  }

  // Throw error if value not found
  throw std::runtime_error("Value not found");
}

// Print list
#include <iostream>
template <typename T>
void LinkedList<T>::print_list() {
  // Check if list empty
  if (this->head == nullptr) {
    std::cout << "Ø" << std::endl;
    return;
  }
  
  // Traverse list and print each element
  ListNode<T>* current = this->head;
  while (current != nullptr) {
    std::cout << current->value << " ";
    current = current->next;
  }

  std::cout << std::endl;
}

// Default Constructor
template <typename T>
LinkedList<T>::LinkedList() {
  // Initialize head to nullptr
  this->head = nullptr;
}

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
  if (other.head == nullptr) {
    return;
  }

  ListNode<T>* current = new ListNode(other.head->value);
  this->head = current;

  ListNode<T>* temp = other.head->next;
  while (temp != nullptr) {
    current->next = new ListNode(temp->value);
    current = current->next;
    temp = temp->next;
  }
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
  // Traverse list and delete each node
  ListNode<T>* current = this->head;
  while (current != nullptr) {
    ListNode<T>* next = current->next;
    delete current;
    current = next;
  }
}

#endif
