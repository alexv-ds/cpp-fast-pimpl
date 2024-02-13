#pragma once
#include <new>
#include <cstddef>
#include <type_traits>
#include <utility>

template<class T, std::size_t Size, std::size_t Align>
class fpimpl {
public:
  template<class... Args>
  inline explicit fpimpl(Args&& ... args) noexcept(std::is_nothrow_constructible_v<T, Args...>);
  inline ~fpimpl();

  inline fpimpl(const fpimpl& pimpl) noexcept(std::is_nothrow_copy_constructible_v<T>);
  inline fpimpl& operator=(const fpimpl& pimpl) noexcept(std::is_nothrow_copy_assignable_v<T>);

  inline fpimpl(fpimpl&& pimpl) noexcept(std::is_nothrow_move_constructible_v<T>);
  inline fpimpl& operator=(fpimpl&& pimpl) noexcept(std::is_nothrow_move_assignable_v<T>);

  inline T& operator*() noexcept;
  inline const T& operator*() const noexcept;
  inline T* operator->() noexcept;
  inline T const* operator->() const noexcept;

  [[maybe_unused]] friend inline void swap(fpimpl& a, fpimpl& b) {
    std::swap(*a, *b);
  }

private:
  alignas(Align) std::byte storage[Size] = {};
};

// region Impl
// //////////////////////////////////////
// //////////////////////////////////////
// //////////////////////////////////////

template<class T, std::size_t Size, std::size_t Align>
template<class... Args>
inline fpimpl<T, Size, Align>::fpimpl(Args&& ... args) noexcept(std::is_nothrow_constructible_v<T, Args...>) {
  static_assert(sizeof(T) <= Size);
  static_assert(alignof(T) == Align);
  new(this->storage) T(std::forward<Args>(args)...);
}

template<class T, std::size_t Size, std::size_t Align>
inline fpimpl<T, Size, Align>::~fpimpl() {
  reinterpret_cast<T*>(this->storage)->~T();
}

template<class T, std::size_t Size, std::size_t Align>
inline fpimpl<T, Size, Align>::fpimpl(const fpimpl<T, Size, Align>& pimpl)
noexcept(std::is_nothrow_copy_constructible_v<T>) {
  new(this->storage) T(*pimpl);
}

template<class T, std::size_t Size, std::size_t Align>
inline fpimpl<T, Size, Align>::fpimpl(fpimpl<T, Size, Align>&& pimpl)
noexcept(std::is_nothrow_move_constructible_v<T>) {
  new(this->storage) T(std::move(*pimpl));
}

template<class T, std::size_t Size, std::size_t Align>
inline fpimpl<T, Size, Align>& fpimpl<T, Size, Align>::operator=(const fpimpl<T, Size, Align>& pimpl)
noexcept(std::is_nothrow_copy_assignable_v<T>) {
  if (this == &pimpl) {
    return *this;
  }
  **this = *pimpl;
  return *this;
}

template<class T, std::size_t Size, std::size_t Align>
inline fpimpl<T, Size, Align>& fpimpl<T, Size, Align>::operator=(fpimpl<T, Size, Align>&& pimpl)
noexcept(std::is_nothrow_move_assignable_v<T>) {
  **this = std::move(*pimpl);
  return *this;
}

template<class T, std::size_t Size, std::size_t Align>
inline T& fpimpl<T, Size, Align>::operator*() noexcept {
  return *reinterpret_cast<T*>(this->storage);
}

template<class T, std::size_t Size, std::size_t Align>
inline const T& fpimpl<T, Size, Align>::operator*() const noexcept {
  return *reinterpret_cast<const T*>(this->storage);
}

template<class T, std::size_t Size, std::size_t Align>
T const* fpimpl<T, Size, Align>::operator->() const noexcept {
  return &**this;
}

template<class T, std::size_t Size, std::size_t Align>
T* fpimpl<T, Size, Align>::operator->() noexcept {
  return &**this;
}
//endregion
