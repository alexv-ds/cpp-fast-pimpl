# cpp-fast-pimpl - impelementation fast pimpl idiom

[![ci-tests](https://github.com/alexv-ds/cpp-fast-pimpl/actions/workflows/ci-tests.yml/badge.svg?branch=main&event=push)](https://github.com/alexv-ds/cpp-fast-pimpl/actions/workflows/ci-tests.yml)
[![codecov](https://codecov.io/gh/alexv-ds/cpp-fast-pimpl/graph/badge.svg?token=KCVH4WEFUK)](https://codecov.io/gh/alexv-ds/cpp-fast-pimpl)
![GitHub](https://img.shields.io/github/license/sasichkamega/cpp-fast-pimpl)
![GitHub tag (with filter)](https://img.shields.io/github/v/tag/sasichkamega/cpp-fast-pimpl)

## Introduction

There are several techniques to hide the implementation details of a class, one of which are the idioms `pimpl`
and `fast pimpl`.
Their essence is to create some opaque (hidden) class where the implementation details will be located,
and put a pointer to the hidden class in the public class.

## Differences between `pimpl` and `fast pimpl`

The difference between `pimpl` and `fast pimpl` is that in the first case you put a pointer to the hidden class in the
public class, and in the constructor you allocate and initialize the hidden class. The disadvantage of this approach is
that the public class and the hidden class are in different places in the heap, which is not very cache friendly.

In `fast pimpl` you create a public class and allocate additional space for the hidden class, and in the constructor you
initialize the additional space with your hidden class, thus all your data in the heap will lie next to each other -
this will give a performance boost. Among the disadvantages of `fast pimpl` it should be noted that you will need to
know the size and aligment of the hidden class at the compilation stage.

## Using `fpimpl.hpp`

### Use CPM.cmake ([more info](https://github.com/cpm-cmake/CPM.cmake))

```cmake
CPMAddPackage("gh:alexv-ds/cpp-fast-pimpl@2.0.0-rc.1")
target_link_libraries(example PRIVATE fpimpl::fpimpl)
```

### Git submodule

Add this repository as a submodule of your project and add the dirrectory in your CMakeListst.txt 

```cmake
add_subdirectory("path/to/fpimpl/subproject")
target_link_libraries(example PRIVATE fpimpl::fpimpl)
```

### Header copy

Due to the fact that this library is just a single header file. Simply copy the header file to the location you want. And use it.

## Example

MyClass.hpp

```c++
class MyClass {
public:
  //ctor, dtor - required
  MyClass(); 
  ~MyClass();

  //copy semantics - optional
  MyClass(const MyClass&); 
  MyClass& operator=(const MyClass&); 

  //move semantics - optional
  MyClass(MyClass&&);
  MyClass& operator=(MyClass&&);
private:
  struct Impl;
  fpimpl<Impl, 16, 8> impl; //16 - Impl struct size, 8 - Impl struct aligment 
};
```

MyClass.cpp

```c++
struct MyClass::Impl {
  //some impl
};

//ctor, dtor - required
MyClass::MyClass() = default; 
MyClass::~MyClass() = default;

//copy semantics - optional
MyClass::MyClass(const MyClass&) = default;
MyClass::MyClass& operator=(const MyClass&) = default;

//move semantics - optional
MyClass(MyClass&&) = default;
MyClass& operator=(MyClass&&) = default;
```
