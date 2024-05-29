// Vector.hpp
#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>

// Class representing a dynamic array
template <typename T>
class Vector {
private:
  T* array;             // Pointer to the array holding the elements
  size_t length;        // Number of elements in the vector
  size_t capacity;      // Capacity of the vector
  size_t step;          // Increment step for expanding the vector's capacity

  // Private helper function to resize the array when the capacity is reached
  void resize();
public:
  // Constructors and Destructor
  Vector();                                                 // Default constructor
  Vector(size_t capacity, size_t step);                     // Parameter constructor
  ~Vector();                                                // Destructor

  // Accessors
  T& operator[](int index);                                 // Overloaded subscript operator
  const T& operator[](int index) const;                     // Overloaded const subscript operator
  const size_t size() const;                                // Returns the number of elements in the vector
  const size_t current_capacity() const;                    // Returns the current capacity of the vector

  // Mutators
  void push_back(const T& element);                         // Adds a new element at the end of the vector
  void pop_back();                                          // Removes the last element of the vector

  // Utility
  void print();                                             // Prints all elements in the vector

  // Iterator
  class Iterator {
  private:
    T* ptr;                                                 // Pointer to the current element in the iteration
  public:
    // Constructor
    Iterator(T* ptr) : ptr(ptr) {}

    // Pre-increment operator
    Iterator& operator++() { ++ptr; return *this; }

    // Post-increment operator
    Iterator operator++(int) { Iterator temp = *this; ++ptr; return temp; }

    // Equality operator
    bool operator==(const Iterator& other) const { return ptr == other.ptr; }

    // Inequality operator
    bool operator!=(const Iterator& other) const { return ptr != other.ptr; } 

    // Dereference operator
    T& operator*() { return *ptr; }
  };

  // Iterator functions
  Iterator begin() { return Iterator(array); }                // Returns an iterator pointing to the first element
  Iterator end() { return Iterator(array + length); }         // Returns an iterator pointing to the end (one past last element)
};

// Function definitions
template <typename T>
void Vector<T>::resize() {
  T* copy = new T[capacity += step];
  for (int i = 0; i < length; i++) {
    copy[i] = array[i];
  }

  delete[] array;
  array = copy;
}

template <typename T>
Vector<T>::Vector() : length(0), capacity(10), step(10) {
  array = new T[capacity];
}

template <typename T>
Vector<T>::Vector(size_t capacity, size_t step) : length(0), capacity(capacity), step(step) {
  array = new T[capacity];
}

template <typename T>
Vector<T>::~Vector() {
  delete[] array;
}

template <typename T>
T& Vector<T>::operator[](int index) {
  if (index < 0 || index >= length) throw std::out_of_range("Index out of range");

  return array[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
  if (index < 0 || index >= length) throw std::out_of_range("Index out of range");

  return array[index];
}

template <typename T>
const size_t Vector<T>::size() const {
  return length;
}

template <typename T>
const size_t Vector<T>::current_capacity() const
{
    return capacity;
}

template <typename T>
void Vector<T>::push_back(const T& element) {
  if (length == capacity) {
    resize();
  }

  array[length++] = element;
}

template <typename T>
void Vector<T>::pop_back() {
  if (length > 0) length--;
}

template <typename T>
void Vector<T>::print() {
  for (int i = 0; i < length; i++) {
      std::cout << array[i] << " ";
  }
  std::cout << std::endl;
}

#endif
