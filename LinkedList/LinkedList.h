#ifndef LINKEDLIST_H
#define LINKEDLIST_H


struct ListNode {
  int value;
  ListNode* next;

  ListNode(int value) : value(value), next(nullptr) {}
};

class LinkedList {
private:
  ListNode* head;
public:
  // Accessors
  int at(int index);
  int front();
  int back();

  // Mutators
  void push_front(int value);
  void push_back(int value);

  void remove_all(int value);
  void pop_front();
  void pop_back();

  // Utility
  void print_list();
  
  // Constructors
  LinkedList();
  LinkedList(const LinkedList &other);
  ~LinkedList();
};

#endif
