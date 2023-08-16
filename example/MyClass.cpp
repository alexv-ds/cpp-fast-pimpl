#include "MyClass.hpp"
#include <iostream>

struct MyClass::Impl {
  int var = 0; //and other data
  void print_impl(const char* msg) {
    std::cout << msg << std::endl;
  };
};

void MyClass::print(const char* msg) {
  this->impl->print_impl(msg);
}

//Definitions of constructors / copy constructors / move constructors / copy operators / move operators
//must be defined after the 'Impl' definition
MyClass::MyClass() = default;
MyClass::~MyClass() = default;
