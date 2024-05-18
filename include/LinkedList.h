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
  void add(int value);
  int get(int index);

  void print();
  LinkedList() : first(nullptr) {}
};
