//
// Created by mfbut on 3/10/2018.
//

#ifndef MYVECTOR_MYVECTOR_H
#define MYVECTOR_MYVECTOR_H

#include <sstream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <vector>
#include <ostream>
#include "ConstVectorItr.h"
#include "VectorItr.h"

template<typename T>
class MyVector;

//overloaded out for MyVector. Prints {element1 element2 element3 ...}
//you may choose to make this function a friend of MyVector if you want
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& myVector);

template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& myVector) {
  out << '{';

  for(auto &item: myVector) {
    out << item << ' ';
  }

  out << '}' << std::endl;

  return out;
}

template<typename T>
class MyVector {
 public:

  MyVector();
  explicit MyVector(const unsigned int& numElements); //create numElements empty items
  MyVector(const unsigned int& numElements, const T& value); // create numElements items all initialized to value

  //here I am templating this particular member method over another type U
  //this will allow us to convert things like a vector<vector<string>> to a
  //MyVector<MyVector<string>> which wouldn't be possible othewise
  template <typename U>
  MyVector(const std::vector<U>& values); // create a MyVector with the same values as standard vector
  MyVector(const MyVector& orig); // create a copy of a MyVector
  virtual ~MyVector(); //clean up any dynamically allocated space for a MyVector
  MyVector& operator=(const MyVector& rhs); // make this MyVector have a COPY of all the values in rhs

  unsigned int size() const; // return the
  bool isEmpty() const; //return true if the vector has no elements in it

  T& front(); //return a reference the first element in MyVector
  const T& front() const; //return a const reference the first element in MyVector
  T& back(); //return a reference to the last element in MyVector
  const T& back() const; //return a const reference to the last element in MyVector
  T& at(const unsigned int& index); //return a reference to the element at the specified position
  const T& at(const unsigned int& index) const;  //return a const reference to the element at the specified position
  T& operator[](const unsigned int& index); //return a reference to the element at the specified position
  const T& operator[](const unsigned int& index) const; //return a const reference to the element at the specified position

  //insert a value into the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void insert(const unsigned int& pos, const T& value);
  void insert(const VectorItr<T>& itr, const T& value);
  void insert(const ConstVectorItr<T>& itr, const T& value);

  //remove a value from the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void erase(const unsigned int& pos);
  void erase(const VectorItr<T>& itr);
  void erase(const ConstVectorItr<T>& itr);

  void pushBack(const T& value); // add an element to the end of the vector
  void popBack(); // remove the last element from the vector

  void clear();// remove all the elements from the vector


  ConstVectorItr<T> begin() const;//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> end() const; //get a constant iterator to the end of the vector

  VectorItr<T> begin(); //get a mutating iterator to the beginning of the vector
  VectorItr<T> end();  //get a mutating iterator to the beginning of the vector

  ConstVectorItr<T> cbegin() const;//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> cend() const; //get a constant iterator to the end of the vector

 private:
  std::unique_ptr<T> *array;
  unsigned long numContained, capacity;

};

//this is a nested template declaration.
//this is the right way of doing things if you have a template show up inside another template
//I've given you this because we didn't cover it in class
template<typename T>
template <typename U>
MyVector<T>::MyVector(const std::vector<U>& values) : numContained(values.size()), capacity(values.size()) {
  array = new std::unique_ptr<T>[capacity];

  for(unsigned int i = 0; i < capacity; i++) {
    array[i] = std::make_unique<T>(values.at(i));
  }
}

//FIXME default case with inditalize
template<typename T>
MyVector<T>::MyVector(const unsigned int &numElements) : numContained(numElements), capacity(numElements){
  array = new std::unique_ptr<T>[numElements];

  for(unsigned int i = 0; i < numElements; i++) {
    array[i] = std::make_unique<T>();
  }
}

template<typename T>
MyVector<T>::MyVector(const unsigned int &numElements, const T &value) : numContained(numElements), capacity(numElements) {
  array = new std::unique_ptr<T>[numElements];

  for(unsigned int i = 0; i < numElements; i++) {
    array[i] = std::make_unique<T>(value);
  }
}

template<typename T>
MyVector<T>::MyVector(const MyVector &orig) : numContained(orig.numContained), capacity(orig.capacity){
  array = new std::unique_ptr<T>[capacity];

  for(unsigned int i = 0; i < numContained; i++) {
    array[i] = std::make_unique<T>(orig.at(i));
  }
}

template<typename T>
MyVector<T>::~MyVector() {
  this->capacity = 0;
  this->numContained = 0;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector &rhs) {
  this->capacity = rhs.capacity;
  this->numContained = rhs.numContained;
  //delete[] array;

  this->array = new std::unique_ptr<T>[capacity];

  for(unsigned int i = 0; i < capacity; i++) {
    array[i] = std::make_unique<T>(rhs.at(i));
  }

  return *this;
}

template<typename T>
unsigned int MyVector<T>::size() const {
  return static_cast<unsigned int>(this->numContained);
}
template<typename T>
bool MyVector<T>::isEmpty() const {
  return numContained == 0;
}
template<typename T>
T &MyVector<T>::front() {
  return this->at(0);
}
template<typename T>
const T &MyVector<T>::front() const {
  return this->at(0);
}
template<typename T>
T &MyVector<T>::back() {
  return this->at(numContained - 1);
}
template<typename T>
const T &MyVector<T>::back() const {
  return this->at(numContained - 1);
}
template<typename T>
T &MyVector<T>::at(const unsigned int &index) {
  if (index>=numContained) {
    std::stringstream errorMessage;
    errorMessage << "Out of bounds exception. Attempted to access the vector at "
                 << index << " but there are only " << size() << " elements. " << std::endl;
    throw std::out_of_range(errorMessage.str());
  }

  return *array[index];
}
template<typename T>
const T &MyVector<T>::at(const unsigned int &index) const {
  if (index>=numContained) {
    std::stringstream errorMessage;
    errorMessage << "Out of bounds exception. Attempted to access the vector at "
                 << index << " but there are only " << size() << " elements. " << std::endl;
    throw std::out_of_range(errorMessage.str());
  }

  return *array[index];
}
template<typename T>
T &MyVector<T>::operator[](const unsigned int &index) {
  return this->at(index);
}
template<typename T>
const T &MyVector<T>::operator[](const unsigned int &index) const {
  return this->at(index);
}
template<typename T>
void MyVector<T>::insert(const unsigned int &pos, const T &value) {

  MyVector copy_array(capacity + 1, value);

  for(unsigned long i = 0; i < pos; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
  }
  copy_array.array[pos] = std::make_unique<T>(value);
  for(unsigned long i = pos + 1; i < copy_array.capacity; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i - 1]));
  }

  *this = copy_array;
}
template<typename T>
void MyVector<T>::insert(const VectorItr<T> &itr, const T &value) {
  MyVector copy_array(capacity + 1, value);

  for(unsigned long i = 0; i < itr.pos; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
  }
  copy_array.array[itr.pos] = std::make_unique<T>(value);
  for(unsigned long i = itr.pos + 1; i < copy_array.capacity; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i - 1]));
  }

  *this = copy_array;
}
template<typename T>
void MyVector<T>::insert(const ConstVectorItr<T> &itr, const T &value) {
  MyVector copy_array(capacity + 1, value);

  for(unsigned long i = 0; i < itr.pos; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
  }
  copy_array.array[itr.pos] = std::make_unique<T>(value);
  for(unsigned long i = itr.pos + 1; i < copy_array.capacity; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i - 1]));
  }

  *this = copy_array;
}
template<typename T>
void MyVector<T>::erase(const unsigned int &pos) {
  MyVector copy_array(capacity - 1, *(this->array[0]));

  if(pos == capacity) {
    for(unsigned long i = 0; i < pos - 1 ; i++) {
      copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
    }
  } else {
    for (unsigned long i = 0; i < pos; i++) {
      copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
    }

    for (unsigned long i = pos; i < copy_array.capacity; i++) {
      copy_array.array[i] = std::make_unique<T>(*(this->array[i + 1]));
    }
  }

  *this = copy_array;
}
template<typename T>
void MyVector<T>::erase(const VectorItr<T> &itr) {
  MyVector copy_array(capacity - 1, *(this->array[0]));

  for(unsigned long i = 0; i < itr.pos; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
  }
  for(unsigned long i = itr.pos; i < copy_array.capacity; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i + 1]));
  }

  *this = copy_array;
}
template<typename T>
void MyVector<T>::erase(const ConstVectorItr<T> &itr) {
  MyVector copy_array(capacity - 1, *(this->array[0]));

  for(unsigned long i = 0; i < itr.pos; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i]));
  }
  for(unsigned long i = itr.pos; i < copy_array.capacity; i++) {
    copy_array.array[i] = std::make_unique<T>(*(this->array[i + 1]));
  }

  *this = copy_array;
}
template<typename T>
void MyVector<T>::pushBack(const T &value) {
  auto pos = capacity;

  this->insert(pos, value);
}
template<typename T>
void MyVector<T>::popBack() {
  auto pos = capacity;

  this->erase(pos);
}
template<typename T>
void MyVector<T>::clear() {
  this->capacity = 0;
  this->numContained = 0;
}
template<typename T>
ConstVectorItr<T> MyVector<T>::begin() const {
  return ConstVectorItr<T>(*this, 0);
}
template<typename T>
ConstVectorItr<T> MyVector<T>::end() const {
  return ConstVectorItr<T>(*this, this->capacity);
}
template<typename T>
VectorItr<T> MyVector<T>::begin() {
  return VectorItr<T>(*this, 0);
}
template<typename T>
VectorItr<T> MyVector<T>::end() {
  return VectorItr<T>(*this, this->capacity);
}
template<typename T>
ConstVectorItr<T> MyVector<T>::cbegin() const {
  return ConstVectorItr<T>(*this, 0);
}
template<typename T>
ConstVectorItr<T> MyVector<T>::cend() const {
  return ConstVectorItr<T>(*this, this->capacity);
}

template<typename T>
MyVector<T>::MyVector() : numContained(0), capacity(0) {}

//template <typename T>


#endif //MYVECTOR_MYVECTOR_H
