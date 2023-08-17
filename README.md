# cpp-fast-pimpl - impelementation fast pimpl idiom

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

## Using `FastPimpl.hpp`

Simply copy the header file to the location you want.

## Example

MyClass.hpp

```c++
class MyClass {
public:
  MyClass(); //implement in cpp
  ~MyClass(); //implement in cpp

  //if support for copy semantics is needed
  //MyClass(const MyClass&); //implement in cpp
  //MyClass& operator=(const MyClass&); //implement in cpp

  //if support for move semantics is needed
  //MyClass(MyClass&&); //implement in cpp
  //MyClass& operator=(MyClass&&); //implement in cpp
private:
  struct Impl;
  FastPimpl<Impl, 16, 8> impl; //where 16 - Impl struct size, 8 - Impl struct aligment 
};
```

MyClass.cpp

```c++
struct MyClass::Impl {
  //some impl
};

MyClass::MyClass() = default; //Your implementation or default
MyClass::~MyClass() = default; //Your implementation or default

//copy semantics
MyClass::MyClass(const MyClass&) = default; //optional
MyClass::MyClass& operator=(const MyClass&) = default; //optional

//move semantics
MyClass(MyClass&&) = default; //optional
MyClass& operator=(MyClass&&) = default; //optional
```
