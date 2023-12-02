#include <FastPimpl.hpp>

// Check compilation when type size is smaller than the defined size for FastPimpl
void compile_check_1() {
  FastPimpl<int, sizeof(int) + 1, alignof(int)> pimpl(123);
}
