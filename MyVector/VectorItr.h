//
// Created by mfbut on 3/11/2018.
//

#ifndef MYVECTOR_VECTORITR_H
#define MYVECTOR_VECTORITR_H

//#include "MyVector.h"

template<typename T>
class MyVector;

template<typename T>
class VectorItr {

 public:
  VectorItr(MyVector<T> &vector, int pos);

  VectorItr& operator++(); //pre
  VectorItr operator++(int); //post

  VectorItr& operator--(); // pre
  VectorItr operator--(int); //post

  VectorItr& operator+=(const unsigned int& rhs); //advance rhs elements
  VectorItr operator+(const unsigned int& rhs); //create a new iterator that is rhs elements beyond the current one

  VectorItr& operator-=(const unsigned int& rhs); //go back rhs elements
  VectorItr operator-(const unsigned int& rhs); // create a new iterator that is rhs elements before the current one

  operator bool() const; // true if pointing to an element within the vector
  bool operator!() const; // true if pointing outside the bounds of the vector
  bool operator==(const VectorItr &rhs) const; // true if referring to the same vector and (at the same position or out of bounds)
  bool operator!=(const VectorItr &rhs) const; // opposite of ==

  T& operator*(); //get the element at the current position
  const T& operator*() const; //get the element at the current position

 public:
  MyVector<T> &vector;
  int pos;
};


//Definitions
template<typename T>
VectorItr<T>::VectorItr(MyVector<T> &vector, int pos) : vector(vector), pos(pos) {

}

template<typename T>
VectorItr<T> &VectorItr<T>::operator++() {
  pos ++;
  return *this;
}
template<typename T>
VectorItr<T> VectorItr<T>::operator++(int) {
  return ++(*this);
}
template<typename T>
VectorItr<T> &VectorItr<T>::operator--() {
  pos--;
  return *this;
}
template<typename T>
VectorItr<T> VectorItr<T>::operator--(int) {
  return --(*this);
}
template<typename T>
VectorItr<T> &VectorItr<T>::operator+=(const unsigned int &rhs) {
  pos += rhs;
  return *this;
}
template<typename T>
VectorItr<T> VectorItr<T>::operator+(const unsigned int &rhs) {
  VectorItr copy(*this);
  copy += rhs;
  return copy;
}
template<typename T>
VectorItr<T> &VectorItr<T>::operator-=(const unsigned int &rhs) {
  pos -= rhs;
  return *this;
}
template<typename T>
VectorItr<T> VectorItr<T>::operator-(const unsigned int &rhs) {
  VectorItr copy(*this);
  copy -= rhs;
  return copy;
}

template<typename T>
VectorItr<T>::operator bool() const {
  return pos >= 0 && pos < static_cast<int>(vector.size());
}
template<typename T>
bool VectorItr<T>::operator!() const {
  return !static_cast<bool>(*this);
}
template<typename T>
bool VectorItr<T>::operator==(const VectorItr &rhs) const {
  if (&vector!=&rhs.vector) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return pos == rhs.pos;
  }
}
template<typename T>
bool VectorItr<T>::operator!=(const VectorItr &rhs) const {
  return !(*this == rhs);
}
template<typename T>
T &VectorItr<T>::operator*() {

  //casting const to return value to aviod confusion
  return vector.at(pos);
}
template<typename T>
const T &VectorItr<T>::operator*() const {
  return vector.at(pos);
}


#endif //MYVECTOR_VECTORITR_H
