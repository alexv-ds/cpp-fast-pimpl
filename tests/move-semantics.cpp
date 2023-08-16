#include <catch2/catch_test_macros.hpp>
#include <FastPimpl.hpp>
#include <string>

namespace {

TEST_CASE("'FastPimpl::FastPimpl(FastPimpl&& pimpl)' moves correctly") {
  FastPimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_1("TEST_4dA");
  auto pimpl_2 = std::move(pimpl_1);
  REQUIRE((*pimpl_1).empty());
  REQUIRE((*pimpl_2) == "TEST_4dA");
}

TEST_CASE("'FastPimpl::operator=(FastPimpl&& pimpl)' moves correctly") {
  FastPimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_1("qwerty");
  FastPimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl_2;
  REQUIRE((*pimpl_1) == "qwerty");
  REQUIRE((*pimpl_2).empty());
  pimpl_2 = std::move(pimpl_1);
  REQUIRE((*pimpl_1).empty());
  REQUIRE((*pimpl_2) == "qwerty");
}


}