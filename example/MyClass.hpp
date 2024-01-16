#pragma once
#include <fpimpl.hpp>

class MyClass {
public:
  void print(const char* msg);
  MyClass();
  ~MyClass();
private:
  struct Impl;
  fpimpl<Impl, 4, 4> impl;
};

