#include "LinkedList/LinkedList.h"

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

  return 0;
}
