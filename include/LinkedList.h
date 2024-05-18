#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class ListNode {
public:
  int value;
  ListNode* next;

  ListNode(int value) : value(value), next(nullptr) {}
};

class LinkedList {
private:
  ListNode* head;
public:
  int at(int index);
  
  void push_back(int value);
  void push_front(int value);

  void remove_all(int value);

  void print_list();
  LinkedList() : head(nullptr) {}
};

#endif
