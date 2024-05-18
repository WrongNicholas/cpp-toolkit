#include "LinkedList.h"

void LinkedList::push_front(int index) {
  ListNode* node = new ListNode(index);
  
  if (this->first == nullptr) {
    this->first = node;
    return;
  }

  node->next = this->first;
  this->first = node;
}

void LinkedList::push_back(int value) {
  // Initialize ListNode
  ListNode* node = new ListNode(value);

  if (this->first == nullptr) {
    this->first = node;
    return;
  }

  ListNode* temp = this->first;
  while(temp->next != nullptr) {
    temp = temp->next;
  }

  temp->next = node;
}

int LinkedList::at(int index) {
  ListNode* node = this->first;
  for (int i = 0; i < index; i++) {
    node = node->next;
  }
  int value = node->value;
  return value;
}

#include <iostream>
void LinkedList::print() {
  if (this->first == nullptr) {
    return;
  }

  ListNode* node = this->first;
  std::cout << "[";
  while (node->next != nullptr) {
    std::cout << node->value << ", ";
    node = node->next;
  }
  std::cout << node->value << "]" << std::endl;
}
