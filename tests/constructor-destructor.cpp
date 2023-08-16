#include <mutex>
#include <memory>
#include <catch2/catch_test_macros.hpp>
#include <FastPimpl.hpp>

namespace {

//region TestClass
static bool g_struct_initialised = false;

class TestClass {
public:
  TestClass() : lock(mutex) {
    g_struct_initialised = true;
  }
  ~TestClass() {
    g_struct_initialised = false;
  }
private:
  //only one instance at once
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock;
};

std::mutex TestClass::mutex;
//endregion

TEST_CASE("'FastPimpl::FastPimpl' initializes correctly") {
  REQUIRE(g_struct_initialised == false);
  FastPimpl<TestClass, sizeof(TestClass), alignof(TestClass)> pimpl;
  REQUIRE(g_struct_initialised == true);
}

TEST_CASE("'FastPimpl::~FastPimpl' destructs correctly") {
  auto p_pimpl = std::make_unique<
    FastPimpl<TestClass, sizeof(TestClass), alignof(TestClass)>
  >();
  REQUIRE(g_struct_initialised == true);
  p_pimpl = nullptr;
  REQUIRE(g_struct_initialised == false);
}

//region TestClass2
static int g_var1 = 0;
static int g_var2 = 0;

class TestClass2 {
public:
  TestClass2(int var1, int var2) : lock(mutex) {
    g_var1 = var1;
    g_var2 = var2;
  }
  ~TestClass2() {
    g_var1 = 0;
    g_var2 = 0;
  }
private:
  //only one instance at once
  static std::mutex mutex;
  std::lock_guard<std::mutex> lock;

};
std::mutex TestClass2::mutex;
//endregion

TEST_CASE("'FastPimpl::FastPimpl' pass args correctly") {
  REQUIRE(g_var1 == 0);
  REQUIRE(g_var2 == 0);
  FastPimpl<TestClass2, sizeof(TestClass2), alignof(TestClass2)> pimpl(123, 321);
  REQUIRE(g_var1 == 123);
  REQUIRE(g_var2 == 321);
}

}