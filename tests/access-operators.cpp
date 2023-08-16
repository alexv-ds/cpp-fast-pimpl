#include <catch2/catch_test_macros.hpp>
#include <FastPimpl.hpp>

namespace {

struct TestStruct {
  int a = 5;
};

TEST_CASE("'FastPimpl::operator*()' returns the correct link") {
  FastPimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl;
  REQUIRE((*pimpl).a == 5);
  (*pimpl).a = 9;
  REQUIRE((*pimpl).a == 9);

}

TEST_CASE("'FastPimpl::operator*() const' returns the correct link") {
  const FastPimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl2;
  REQUIRE((*pimpl2).a == 5);
}

TEST_CASE("'FastPimpl::operator->() const' returns the correct pointer") {
  const FastPimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl;
  REQUIRE(pimpl->a == 5);
}

TEST_CASE("'FastPimpl::operator->()' returns the correct pointer") {
  FastPimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl;
  REQUIRE(pimpl->a == 5);
  pimpl->a = 9;
  REQUIRE(pimpl->a == 9);
}

}