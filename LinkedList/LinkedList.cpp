#include "LinkedList.h"

// Return value at index
int LinkedList::at(int index) {
  ListNode* node = this->head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  int value = node->value;
  return value;
}

// Return value at front
int LinkedList::front() {
  return this->head->value;
}

// Return value at back
int LinkedList::back() {
  ListNode* current = this->head;
  while (current->next != nullptr) {
    current = current->next;
  }

  return current->value;
}

// Add new element to front of list
void LinkedList::push_front(int index) {
  ListNode* node = new ListNode(index);
  
  if (this->head == nullptr) {
    this->head = node;
    return;
  }

  node->next = this->head;
  this->head = node;
}

// Add new element to end of list
void LinkedList::push_back(int value) {
  // Initialize ListNode
  ListNode* node = new ListNode(value);

  if (this->head == nullptr) {
    this->head = node;
    return;
  }

  ListNode* temp = this->head;
  while(temp->next != nullptr) {
    temp = temp->next;
  }

  temp->next = node;
}

// Add new element at index
void LinkedList::insert(int index, int value) {
  if (index == 0) {
    this->push_front(value);
    return;
  }

  ListNode* current = this->head;
  for (int i = 1; i < index; i++) {
    current = current->next;
  }

  ListNode* temp = current->next;
  current->next = new ListNode(value);
  current->next->next = temp;
}

// Remove all element(s) from list
void LinkedList::remove_all(int value) {
  if (this->head == nullptr) {
    return;
  }

  // Handle head node(s) with value to remove
  while(this->head != nullptr && this->head->value == value) {
    ListNode* temp = this->head;
    this->head = this->head->next;
    delete temp;
  }

  // Catch for all node(s) removed
  if (this->head == nullptr) {
    return;
  }
  
  // Handle all remaining non-head nodes
  ListNode* current = this->head;

  while (current->next != nullptr) {
    if (current->next->value == value) {
      ListNode* temp = current->next;
      current->next = current->next->next;
      delete temp;
    } else {
      current = current->next;
    }
  }
}

// Remove element at front of list
void LinkedList::pop_front() {
  if (this->head == nullptr) {
    return;
  }

  ListNode* temp = this->head;
  this->head = this->head->next;
  delete temp;
}

// Remove element at end of list
void LinkedList::pop_back() {
  if (this->head == nullptr) {
    return;
  }

  if (this->head->next == nullptr) {
    delete this->head;
    this->head = nullptr;
    return;
  }

  ListNode* temp = this->head;
  while (temp->next->next != nullptr) {
    temp = temp->next;
  }

  delete temp->next;
  temp->next = nullptr;
}

// Clear list
void LinkedList::clear() {
  ListNode* current = this->head;
  while (current != nullptr) {
    ListNode* next = current->next;
    delete current;
    current = next;
  }

  this->head = nullptr;
}

// Print list
#include <iostream>
void LinkedList::print_list() {
  if (this->head == nullptr) {
    std::cout << "Empty!" << std::endl;
    return;
  }

  ListNode* current = this->head;
  while (current != nullptr) {
    std::cout << current->value << " ";
    current = current->next;
  }
  std::cout << std::endl;
}

// Default Constructor
LinkedList::LinkedList() : head(nullptr) { }

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

// Deconstructor
LinkedList::~LinkedList() {
  ListNode* current = this->head;

  while (current != nullptr) {
    ListNode* next = current->next;
    delete current;
    current = next;
  }
}
