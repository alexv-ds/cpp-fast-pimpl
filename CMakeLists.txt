cmake_minimum_required(VERSION 3.21)

project(fpimpl
  VERSION 2.0.0
  DESCRIPTION "C++ modern fast pimpl idiom"
  HOMEPAGE_URL "https://github.com/sasichkamega/cpp-fast-pimpl"
  LANGUAGES CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "In-source builds not allowed")
endif()

##################################
############ OPTIONS #############
##################################
set(FPIMPL_BUILD_EXAMPLE ${PROJECT_IS_TOP_LEVEL} CACHE BOOL "Build example")
set(FPIMPL_BUILD_TESTS ${PROJECT_IS_TOP_LEVEL} CACHE BOOL "Build tests")
set(FPIMPL_ENABLE_WALL_WERROR ${PROJECT_IS_TOP_LEVEL} CACHE BOOL "Enable -Wall -Werror compile flags")
set(FPIMPL_INSTALL ON CACHE BOOL "Generate install targets")

if(FPIMPL_BUILD_TESTS)
  set(BUILD_TESTING ON CACHE BOOL "") 
endif()

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

##################################
########### TARGETS ##############
##################################
add_library(fpimpl INTERFACE include/fpimpl.hpp)
add_library(${PROJECT_NAME}::fpimpl ALIAS fpimpl)

target_compile_features(fpimpl INTERFACE cxx_std_17)
target_compile_options(fpimpl INTERFACE
    $<$<BOOL:${FPIMPL_ENABLE_WALL_WERROR}>:
      $<IF:$<CXX_COMPILER_ID:MSVC>,/W4 /WX,-Wall -Wextra -Wpedantic -Werror>  
    >
)

target_include_directories(fpimpl INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

if(FPIMPL_BUILD_EXAMPLE)
  add_executable(example
    example/main.cpp
    example/MyClass.cpp
    example/MyClass.hpp
  )
  target_link_libraries(example PRIVATE fpimpl) 
endif()

##################################
############ TESTS ###############
##################################
if(FPIMPL_BUILD_TESTS OR FPIMPL_INSTALL)
  include(cmake/get_cpm.cmake)
endif()

if(FPIMPL_BUILD_TESTS)
  CPMAddPackage(GITHUB_REPOSITORY catchorg/Catch2 VERSION 3.5.2 OPTIONS
    "CATCH_INSTALL_DOCS OFF"
    "CATCH_INSTALL_EXTRAS OFF"
  )
  list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
  include(CTest)
  include(Catch)

  add_executable(tests
    tests/constructor-destructor.cpp
    tests/access-operators.cpp
    tests/copy-semantics.cpp
    tests/move-semantics.cpp
    tests/compile-check.cpp
  )
  target_link_libraries(tests PRIVATE
    fpimpl
    Catch2::Catch2WithMain
  )
  catch_discover_tests(tests)
endif()

##################################
########### INSTALL ##############
##################################
if(FPIMPL_INSTALL)
  CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.11.1")

  packageProject(
    NAME ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    NAMESPACE ${PROJECT_NAME}
    BINARY_DIR ${PROJECT_BINARY_DIR}
    INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
    INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT YES
  )
endif()
