#include <catch2/catch_test_macros.hpp>
#include <fpimpl.hpp>

namespace {

struct TestStruct {
  int a = 5;
};

TEST_CASE("'fpimpl::operator*()' returns the correct link") {
  fpimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl;
  REQUIRE((*pimpl).a == 5);
  (*pimpl).a = 9;
  REQUIRE((*pimpl).a == 9);

}

TEST_CASE("'fpimpl::operator*() const' returns the correct link") {
  const fpimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl2;
  REQUIRE((*pimpl2).a == 5);
}

TEST_CASE("'fpimpl::operator->() const' returns the correct pointer") {
  const fpimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl;
  REQUIRE(pimpl->a == 5);
}

TEST_CASE("'fpimpl::operator->()' returns the correct pointer") {
  fpimpl<TestStruct, sizeof(TestStruct), alignof(TestStruct)> pimpl;
  REQUIRE(pimpl->a == 5);
  pimpl->a = 9;
  REQUIRE(pimpl->a == 9);
}

}