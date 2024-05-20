#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Struct defining a node in linked list
struct ListNode {
  int value;
  ListNode* next;
  
  ListNode(int value) : value(value), next(nullptr) {}
};

// Class representing singly linked list
class LinkedList {
private:
  ListNode* head;                          // Pointer to first node in list 
public:                                    
  // Constructors and Destructor           
  LinkedList();                            // Default constructor
  LinkedList(const LinkedList &other);     // Copy constructor
  ~LinkedList();                           // Destructor

  // Accessors
  int value_at(int index);                 // Returns value stored at specific index
  int front();                             // Returns value at list head
  int back();                              // Returns value at list tail
  int& operator[](int index);              // Overloaded subscript operator

  int size() const;                        // Returns number of elements
  bool empty() const;                      // Checks if list empty

  // Mutators
  void push_front(int value);              // Adds new element at head
  void push_back(int value);               // Adds new element at tail
  void insert(int index, int value);       // Adds new element at specified index
  
  void remove_all(int value);              // Removes all elements of value
  void pop_front();                        // Removes head element
  void pop_back();                         // Removes tail element
  void clear();                            // Removes all elements

  // Utility
  int find(int value) const;               // Finds index of first occurance of value
  void print_list();                       // Prints all elements
};

#endif
