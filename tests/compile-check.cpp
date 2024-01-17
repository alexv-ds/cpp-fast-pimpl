#include <fpimpl.hpp>

// Check compilation when type size is smaller than the defined size for fpimpl
void compile_check_1() {
  fpimpl<int, sizeof(int) + 1, alignof(int)> pimpl(123);
}
