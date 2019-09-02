#include <string>
#include <iostream>
#include <vector>
#include "MyVector.h"

class NoDefault {
 public:
  NoDefault(const int& value) : value(value) {}

  int value;
};

std::ostream& operator<<(std::ostream& out, const NoDefault& noDefault) {
  out << noDefault.value;
  return out;
}

template <typename T>
void simpleMyVectorConstItrPrint(const MyVector<T>& vec){
  for(auto itr = vec.cbegin(); itr != vec.cend(); ++itr){
    std::cout << *itr << ' ';
  }
  std::cout << std::endl;
}

template <typename T>
void reverseMyVectorItrPrintButFirst(const MyVector<T>& vec){
  auto itr = vec.cend() - 1u;
  for(; itr != vec.cbegin(); --itr){
    std::cout << *itr << ' ';
  }
  std::cout << std::endl;
}




template <typename T>
void steppedMyVectorItrPrint(const MyVector<T>& vec, const unsigned int& stepAmount){
  for(auto itr = vec.cbegin(); itr != vec.cend(); itr += stepAmount){
    std::cout << *itr << ' ';
  }
  std::cout << std::endl;
}

template <typename T>
void MyVectorItrSet(MyVector<T>& vec, const std::vector<T>& values){
  auto srcItr = values.cbegin();
  for(auto destItr = vec.begin(); !(destItr == vec.end() || srcItr == values.cend()); ++destItr, ++srcItr){
    *destItr = *srcItr;
  }
  std::cout << std::endl;
}


int main() {
  MyVector<int> intVec(std::vector<int>{1,2,3});
  MyVector<std::string> stringVec(std::vector<std::string>{"how", "now", "brown", "cow"});
  MyVector<NoDefault> noDefaultVec(std::vector<NoDefault>{7,8,9,10,11});
  MyVector<MyVector<NoDefault>> vecvec(2, noDefaultVec);

  std::cout << "intVec = " << intVec << std::endl;
  std::cout << "stringVec = " << stringVec << std::endl;
  std::cout << "noDefaultVec = " << noDefaultVec << std::endl;
  std::cout << "vecvec = " << vecvec << std::endl;

  try{
    intVec.insert(4, 12);
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on insertion handled" << std::endl;
  }

  try{
    intVec.erase(7);
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on erase handled" << std::endl;
  }

  try{
    intVec.at(8);
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on at handled" << std::endl;
  }

  try{
    intVec[11];
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on bracket handled" << std::endl;
  }

  try{
    intVec.insert(intVec.begin() +19u, 83);
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on iterator insert handled" << std::endl;
  }

  try{
    intVec.erase(intVec.cbegin() +24u);
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on iterator erase handled" << std::endl;
  }

  try{
    *(intVec.cbegin() +5u);
  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on const iterator dereference handled" << std::endl;
  }

  try{
    auto itr = intVec.begin();
    *itr =9;
    *(itr + 13u) = 24;

  }catch(std::out_of_range& oorError){
    std::cout << "Out of range on iterator dereference handled" << std::endl;
  }

  std::cout << "hello" << std::endl;
  return 0;
}