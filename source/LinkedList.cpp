#include "LinkedList.h"

void LinkedList::push_front(int index) {
  ListNode* node = new ListNode(index);
  
  if (this->head == nullptr) {
    this->head = node;
    return;
  }

  node->next = this->head;
  this->head = node;
}

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

int LinkedList::at(int index) {
  ListNode* node = this->head;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  int value = node->value;
  return value;
}

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

#include <iostream>
void LinkedList::print_list() {
  if (this->head == nullptr) {
    return;
  }

  ListNode* node = this->head;
  std::cout << "[";
  while (node->next != nullptr) {
    std::cout << node->value << ", ";
    node = node->next;
  }
  std::cout << node->value << "]" << std::endl;
}
