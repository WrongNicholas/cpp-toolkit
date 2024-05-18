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
  int get(int index);
  
  // Add methods
  void addLast(int value);
  void addFirst(int value);

  void print();
  LinkedList() : first(nullptr) {}
};
