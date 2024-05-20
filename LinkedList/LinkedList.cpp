#include "LinkedList.h"
#include <stdexcept>

// Return value at index
int LinkedList::value_at(int index) {
  // Check if index is within lower range
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  
  // Traverse list until reaching index
  int i = 0;
  ListNode* current = this->head;
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
int LinkedList::front() {
  // Check if list is empty
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  // Return head node
  return this->head->value;
}

// Return value at back of list
int LinkedList::back() {
  // Check if list is empty
  if (this->head == nullptr) {
    throw std::out_of_range("List is empty");
  }

  // Traverse list until current node is tail
  ListNode* current = this->head;
  while (current->next != nullptr) {
    current = current->next;
  }
  
  // Return tail node
  return current->value;
}

// Overload subscript operator
int& LinkedList::operator[](int index) {
  // Check if index is within lower range
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }
  
  // Traverse list until current node matches index
  int i = 0;
  ListNode* current = this->head;
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

// Add new element to front of list
void LinkedList::push_front(int value) {
  // Make new node with provided value 
  ListNode* node = new ListNode(value);
  
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
void LinkedList::push_back(int value) {
  // Initialize ListNode
  ListNode* node = new ListNode(value);

  // Check if list empty
  if (this->head == nullptr) {
    this->head = node;
    return;
  }

  // Traverse list to find tail
  ListNode* temp = this->head;
  while(temp->next != nullptr) {
    temp = temp->next;
  }
  
  // Set tail's next to new node
  temp->next = node;
}

// Add new element at index
void LinkedList::insert(int index, int value) {
  if (index < 0) {
    throw std::out_of_range("Index out of range");
  }

  // Call push_front if index is 0
  if (index == 0) {
    this->push_front(value);
    return;
  }

  // Traverse list until desired index - 1
  ListNode* current = this->head;
  for (int i = 1; i < index; i++) {
    // Check if in bounds
    if (current == nullptr) {
      throw std::out_of_range("Index out of range");
    }
    
    // Move to next node
    current = current->next;
  }
  
  // Insert node between current and current's next
  ListNode* node = new ListNode(value);
  node->next = current->next;
  current->next = node;
}

// Remove all element(s) of value from list
void LinkedList::remove_all(int value) {
  // Check if list empty
  if (this->head == nullptr) {
    return;
  }

  // Remove head node(s) of value
  while(this->head != nullptr && this->head->value == value) {
    ListNode* temp = this->head;
    this->head = this->head->next;
    delete temp;
  }

  // Check if list is empty after removing head node(s)
  if (this->head == nullptr) {
    return;
  }
  
  // Remove all remaining non-head nodes of value
  ListNode* current = this->head;
  while (current->next != nullptr) {
    // Remove current's next if matches value
    if (current->next->value == value) {
      ListNode* temp = current->next;
      current->next = current->next->next;
      delete temp;
      
    } else {
      // Move to next node
      current = current->next;
    }
  }
}

// Remove element at front of list
void LinkedList::pop_front() {
  // Check if list empty
  if (this->head == nullptr) {
    return;
  }
  
  // Remove first node
  ListNode* temp = this->head;
  this->head = this->head->next;
  delete temp;
}

// Remove element at end of list
void LinkedList::pop_back() {
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
  ListNode* temp = this->head;
  while (temp->next->next != nullptr) {
    temp = temp->next;
  }

  // Remove tail
  delete temp->next;
  temp->next = nullptr;
}

// Clear list
void LinkedList::clear() {
  // Traverse list and delete  nodes
  ListNode* current = this->head;
  while (current != nullptr) {
    ListNode* next = current->next;
    delete current;
    current = next;
  }

  // Reset head pointer
  this->head = nullptr;
}

// Print list
#include <iostream>
void LinkedList::print_list() {
  // Check if list empty
  if (this->head == nullptr) {
    std::cout << "Ø" << std::endl;
    return;
  }
  
  // Traverse list and print each element
  ListNode* current = this->head;
  while (current != nullptr) {
    std::cout << current->value << " ";
    current = current->next;
  }

  std::cout << std::endl;
}

// Default Constructor
LinkedList::LinkedList() {
  // Initialize head to nullptr
  this->head = nullptr;
}

// Copy Constructor
LinkedList::LinkedList(const LinkedList& other) {
  if (other.head == nullptr) {
    return;
  }

  ListNode* current = new ListNode(other.head->value);
  this->head = current;

  ListNode* temp = other.head->next;
  while (temp != nullptr) {
    current->next = new ListNode(temp->value);
    current = current->next;
    temp = temp->next;
  }
}

// Destructor
LinkedList::~LinkedList() {
  // Traverse list and delete each node
  ListNode* current = this->head;
  while (current != nullptr) {
    ListNode* next = current->next;
    delete current;
    current = next;
  }
}
