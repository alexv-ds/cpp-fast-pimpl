#include <fpimpl.hpp>

// Check compilation when type size is smaller than the defined size for fpimpl
void compile_check_1() {
  fpimpl<int, sizeof(int) + 1, alignof(int)> pimpl(123);
}

// Check compilation with different alignments
void compile_check_2() {
  { fpimpl<std::int16_t, 2, 2> pimpl; }

  { fpimpl<std::int16_t, 2, 4> pimpl; }
  { fpimpl<std::int16_t, 2, 8> pimpl; }
  { fpimpl<std::int16_t, 2, 16> pimpl; }

  { fpimpl<std::int16_t, 4, 4> pimpl; }
  { fpimpl<std::int16_t, 4, 8> pimpl; }
  { fpimpl<std::int16_t, 4, 16> pimpl; }

  { fpimpl<std::int16_t, 8, 8> pimpl; }
  { fpimpl<std::int16_t, 8, 16> pimpl; }

  { fpimpl<std::int16_t, 16, 16> pimpl; }
}