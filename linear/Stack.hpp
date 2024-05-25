// Stack.hpp
#ifndef STACK_H
#define STACK_H

// Include LinkedList header for stack implementation
#include "LinkedList.hpp"

template <typename T>
class Stack {
private:
  // Internal LinkedList for storing stack elements
  LinkedList<T> list;

public:
  // Constructor and Destructor
  Stack();
  ~Stack();

  // Public Functions
  void push(const T& item);         // Push an item on top of the stack
  void pop();                       // Remove the top item of the stack
  const T& peek() const;            // Peek at the top item of the stack (const)
  T& top();                         // Access the top item of the stack
  const bool empty() const;         // Check if the stack is empty
  const int size() const;           // Get the number of elements in the stack
  void clear();                     // Clear all elements from the stack
};

template <typename T>
Stack<T>::Stack() {

}

template <typename T>
Stack<T>::~Stack() {
  list.clear();
}

template <typename T>
void Stack<T>::push(const T& item) {
  list.push_front(item);
}

template <typename T>
void Stack<T>::pop() {
  list.pop_front();
}

template <typename T>
T& Stack<T>::top() {
  return list.front();
}

template <typename T>
const T& Stack<T>::peek() const {
  return list.front();
}

template <typename T>
const bool Stack<T>::empty() const {
  return list.empty();
}

template <typename T>
const int Stack<T>::size() const {
  return list.size();
}

template <typename T>
void Stack<T>::clear() {
  list.clear();
}
#endif
