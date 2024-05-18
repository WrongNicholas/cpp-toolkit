#include "LinkedList.h"

int main() {
  LinkedList linkedList;
  for (int i = 0; i < 10000; i++) {
    linkedList.add(i);
  }

  linkedList.print();

  return 0;
}
