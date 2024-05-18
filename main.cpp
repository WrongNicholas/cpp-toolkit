#include "LinkedList.h"

int main() {
  LinkedList linkedList;
  for (int i = 0; i < 10; i++) {
    linkedList.push_front(i);
  }

  linkedList.print();

  return 0;
}
