#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <iostream>

template <typename T>
class Vector {
private:
  T* data;

  size_t length;
  size_t capacity;
  size_t stride;

  void resize();
public:
  Vector();
  Vector(size_t capacity, size_t stride);
  ~Vector();

  // Accessors
  T& operator[](int index);
  const T& operator[](int index) const;
  const size_t size() const;

  // Mutators
  void push_back(const T& element);
  void pop_back();

  // Utility
  void print();

  // Iterator
  class Iterator {
  private:
    T* ptr;
  public:
    Iterator(T* ptr) : ptr(ptr) {}

    Iterator& operator++() {
      ++ptr;
      return *this;
    }

    Iterator operator++(int) { 
      Iterator temp = *this;
      ++ptr;
      return temp;
    }

    bool operator==(const Iterator& other) const { return ptr == other.ptr; }

    bool operator!=(const Iterator& other) const { return ptr != other.ptr; } 

    T& operator*() { return *ptr; }
  };

  Iterator begin() { return Iterator(data); }

  Iterator end() { return Iterator(data + length); }
};

template <typename T>
void Vector<T>::resize() {
  T* copy = new T[capacity += stride];
  for (int i = 0; i < length; i++) {
    copy[i] = data[i];
  }

  delete[] data;
  data = copy;
}

template <typename T>
Vector<T>::Vector() : length(0), capacity(10), stride(10) {
  data = new T[capacity];
}

template <typename T>
Vector<T>::Vector(size_t capacity, size_t stride) : length(0), capacity(capacity), stride(stride) {
  data = new T[capacity];
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data;
}

template <typename T>
T& Vector<T>::operator[](int index) {
  if (index < 0 || index >= length) throw std::out_of_range("Index out of range");

  return data[index];
}

template <typename T>
const T& Vector<T>::operator[](int index) const {
  if (index < 0 || index >= length) throw std::out_of_range("Index out of range");

  return data[index];
}

template <typename T>
const size_t Vector<T>::size() const {
  return length;
}

template <typename T>
void Vector<T>::push_back(const T& element) {
  if (length == capacity) {
    resize();
  }

  data[length++] = element;
}

template <typename T>
void Vector<T>::pop_back() {
  if (length > 0) length--;
}

template <typename T>
void Vector<T>::print() {
  for (int i = 0; i < length; i++) {
      std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

#endif
