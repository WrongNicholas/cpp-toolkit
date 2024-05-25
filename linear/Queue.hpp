#ifndef QUEUE_H
#define QUEUE_H

// Include LinkedList header for queue implementation
#include "LinkedList.hpp"

template <typename T>
class Queue {
private:
  LinkedList<T> list;
public:
  // Constructor and Destructor
  Queue();                      // Default constructor
  ~Queue();                     // Destructor

  // Accessors
  T& front();                   // Access the front item of the queue
  const T& front() const;       // Access the front item of the queue (const)
  const bool empty() const;     // Check if the queue is empty
  const int size() const;       // Get the size of the queue

  // Mutators
  void push(const T& value);    // Push an item to the back of the queue
  void pop();                   // Remove the item from the front of the queue
  void clear();                 // Clears the queue
};

// Function definitions
template <typename T>
Queue<T>::Queue() {

}

template <typename T>
Queue<T>::~Queue() {
  clear();
}

template <typename T>
const T& Queue<T>::front() const {
  return list.front();
}

template <typename T>
T& Queue<T>::front() {
  return list.front();
}

template <typename T>
const bool Queue<T>::empty() const {
  return list.empty();
}

template <typename T>
const int Queue<T>::size() const {
  return list.size();
}

template <typename T>
void Queue<T>::push(const T& value) {
  list.push_back(value);
}

template <typename T>
void Queue<T>::pop() {
  list.pop_front();
}

template <typename T>
void Queue<T>::clear() {
  list.clear();
}

#endif
