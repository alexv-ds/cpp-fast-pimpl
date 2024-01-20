#include <catch2/catch_test_macros.hpp>
#include <fpimpl.hpp>
#include <string>

namespace {

TEST_CASE("'fpimpl::fpimpl(const fpimpl& pimpl)' copies correctly") {
  fpimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_1("TEST_12");
  auto pimpl_2 = pimpl_1;
  REQUIRE((*pimpl_1) == "TEST_12");
  REQUIRE((*pimpl_2) == "TEST_12");
}

TEST_CASE("'fpimpl::operator=(const fpimpl& pimpl)' copies correctly") {
  fpimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_1("TEST_12");
  fpimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_2;
  REQUIRE((*pimpl_1) == "TEST_12");
  REQUIRE((*pimpl_2).empty());
  pimpl_2 = pimpl_1;
  REQUIRE((*pimpl_1) == "TEST_12");
  REQUIRE((*pimpl_2) == "TEST_12");
}

}