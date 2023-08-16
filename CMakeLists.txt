cmake_minimum_required(VERSION 3.22)
project(FastPimpl VERSION 1.0.0 LANGUAGES CXX)

if(NOT PROJECT_IS_TOP_LEVEL)
  message(FATAL_ERROR "This Cmake project is made for running tests. You cannot use it as a subproject. \
                       To use FastPimpl.h - copy the file to the desired location and include it.")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(BUILD_TESTING ON CACHE BOOL "")

if(MSVC)
  add_compile_options(/W3)
else()
  add_compile_options(-Wall)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")
endif()

include(FetchContent)
fetchcontent_declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)

fetchcontent_makeavailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

add_executable(example
  FastPimpl.hpp
  example/main.cpp
  example/MyClass.cpp example/MyClass.hpp)
target_include_directories(example PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tests
  FastPimpl.hpp
  tests/constructor-destructor.cpp
  tests/access-operators.cpp
  tests/copy-semantics.cpp
  tests/move-semantics.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
catch_discover_tests(tests)
add_dependencies(tests example) #for example compilation check if we build tests only
