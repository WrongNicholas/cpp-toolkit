#include "LinkedList.h"

int main() {
  LinkedList linkedList;
  for (int i = 0; i < 10; i++) {
    linkedList.push_front(i);
  }
  
  linkedList.remove_all(-4);

  linkedList.print_list();

  return 0;
}
