#include <catch2/catch_test_macros.hpp>
#include <fpimpl.hpp>
#include <string>

namespace {

TEST_CASE("'fpimpl::operator=(const fpimpl& pimpl)' correctly copies with self assign") {
  fpimpl<std::string, sizeof(std::string), alignof(std::string)> pimpl("SELF COPY");
  void* ptr1 = &*pimpl;
  pimpl = pimpl;
  void* ptr2 = &*pimpl;

  REQUIRE(ptr1 == ptr2);
  REQUIRE((*pimpl) == "SELF COPY");
}

}