#include "LinkedList/LinkedList.h"
#include <iostream>

int main() {
  LinkedList linkedList;
  for (int i = 0; i < 99; i++) {
    linkedList.push_back(i);
  }
  
  for (int i = 0; i < 99; i += 2) {
    linkedList.remove_all(i);
  }
  
  linkedList.pop_front();
  linkedList.pop_back();

  linkedList.print_list();

  // Test Copy Constructor
  LinkedList copiedLinkedList(linkedList);
  copiedLinkedList.pop_back();
  copiedLinkedList.pop_front();
  copiedLinkedList.print_list();

  std::cout << copiedLinkedList.front() << " " << copiedLinkedList.back() << std::endl;

  return 0;
}
