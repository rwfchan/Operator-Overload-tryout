//
// Created by mfbut on 3/11/2018.
//

#ifndef MYVECTOR_CONSTVECTORITR_H
#define MYVECTOR_CONSTVECTORITR_H

//#include "MyVector.h"

template<typename T>
class MyVector;

template <typename T>
class ConstVectorItr {
 public:
  ConstVectorItr(const MyVector<T> &vector, int pos);
  ConstVectorItr& operator++(); //pre
  ConstVectorItr operator++(int); //post

  ConstVectorItr& operator--(); // pre
  ConstVectorItr operator--(int); //post

  ConstVectorItr& operator+=(const unsigned int& rhs); //advance rhs elements
  ConstVectorItr operator+(const unsigned int& rhs); //create a new iterator that is rhs elements beyond the current one

  ConstVectorItr& operator-=(const unsigned int& rhs); //go back rhs elements
  ConstVectorItr operator-(const unsigned int& rhs); // create a new iterator that is rhs elements before the current one

  operator bool() const; // true if pointing to an element within the vector
  bool operator!() const; // true if pointing outside the bounds of the vector
  bool operator==(const ConstVectorItr& rhs) const; // true if referring to the same vector and (at the same position or out of bounds)
  bool operator!=(const ConstVectorItr& rhs) const; // opposite of ==

  const T& operator*() const; //get the element at the current position

 public:
  const MyVector<T>& vector;
  int pos;
};


//Definitions
template<typename T>
ConstVectorItr<T>::ConstVectorItr(const MyVector<T> &vector, int pos) : vector(vector), pos(pos) {

}

template<typename T>
ConstVectorItr<T> &ConstVectorItr<T>::operator++() {
  pos ++;
  return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator++(int) {
  return ++(*this);
}
template<typename T>
ConstVectorItr<T> &ConstVectorItr<T>::operator--() {
  pos--;
  return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator--(int) {
  return --(*this);
}
template<typename T>
ConstVectorItr<T> &ConstVectorItr<T>::operator+=(const unsigned int &rhs) {
  pos += rhs;
  return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator+(const unsigned int &rhs) {
  ConstVectorItr copy(*this);
  copy += rhs;
  return copy;
}
template<typename T>
ConstVectorItr<T> &ConstVectorItr<T>::operator-=(const unsigned int &rhs) {
  pos -= rhs;
  return *this;
}
template<typename T>
ConstVectorItr<T> ConstVectorItr<T>::operator-(const unsigned int &rhs) {
  ConstVectorItr copy(*this);
  copy -= rhs;
  return copy;
}

template<typename T>
ConstVectorItr<T>::operator bool() const {
  return pos >= 0 && pos < vector.size();
}
template<typename T>
bool ConstVectorItr<T>::operator!() const {
  return !static_cast<bool>(*this);
}
template<typename T>
bool ConstVectorItr<T>::operator==(const ConstVectorItr &rhs) const {
  if (&vector!=&rhs.vector) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return pos == rhs.pos;
  }
}
template<typename T>
bool ConstVectorItr<T>::operator!=(const ConstVectorItr &rhs) const {
  return !(*this == rhs);
}

template<typename T>
const T &ConstVectorItr<T>::operator*() const {
  return vector.at(pos);
}

#endif //MYVECTOR_CONSTVECTORITR_H
