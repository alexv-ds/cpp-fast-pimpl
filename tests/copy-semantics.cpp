#include <catch2/catch_test_macros.hpp>
#include <FastPimpl.hpp>
#include <string>

namespace {

TEST_CASE("'FastPimpl::FastPimpl(const FastPimpl& pimpl)' copies correctly") {
  FastPimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_1("TEST_12");
  auto pimpl_2 = pimpl_1;
  REQUIRE((*pimpl_1) == "TEST_12");
  REQUIRE((*pimpl_2) == "TEST_12");
}

TEST_CASE("'FastPimpl::operator=(const FastPimpl& pimpl)' copies correctly") {
  FastPimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_1("TEST_12");
  FastPimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_2;
  REQUIRE((*pimpl_1) == "TEST_12");
  REQUIRE((*pimpl_2).empty());
  pimpl_2 = pimpl_1;
  REQUIRE((*pimpl_1) == "TEST_12");
  REQUIRE((*pimpl_2) == "TEST_12");
}

}