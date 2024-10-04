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

public:
  DoublyLinkedList() : head(nullptr), tail(nullptr), list_size(0) {}
  ~DoublyLinkedList();

  void push_front(const T& value);
};

template <typename T>
void DoublyLinkedList<T>::push_front(const T& value) {

}

#endif
