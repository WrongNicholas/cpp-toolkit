class ListNode {
public:
  int value;
  ListNode* next;

  ListNode(int value) : value(value), next(nullptr) {}
};

class LinkedList {
private:
  ListNode* first;
public:
  // Accessors
  int at(int index);
  
  // Add methods
  void push_back(int value);
  void push_front(int value);

  void print();
  LinkedList() : first(nullptr) {}
};
