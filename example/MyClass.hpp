#pragma once
#include <FastPimpl.hpp>

class MyClass {
public:
  void print(const char* msg);
  MyClass();
  ~MyClass();
private:
  struct Impl;
  FastPimpl<Impl, 4, 4> impl;
};

