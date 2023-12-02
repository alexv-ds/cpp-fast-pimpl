#pragma once
#include <new>
#include <cstddef>
#include <type_traits>
#include <utility>

template<class T, std::size_t Size, std::size_t Align>
class FastPimpl {
public:
  template<class... Args>
  inline explicit FastPimpl(Args&& ... args) noexcept(std::is_nothrow_constructible_v<T, Args...>);
  inline ~FastPimpl() /*noexcept(std::is_nothrow_destructible_v<T>)*/;

  inline FastPimpl(const FastPimpl& pimpl) noexcept(std::is_nothrow_copy_constructible_v<T>);
  inline FastPimpl& operator=(const FastPimpl& pimpl) noexcept(std::is_nothrow_copy_assignable_v<T>);

  inline FastPimpl(FastPimpl&& pimpl) noexcept(std::is_nothrow_move_constructible_v<T>);
  inline FastPimpl& operator=(FastPimpl&& pimpl) noexcept(std::is_nothrow_move_assignable_v<T>);

  inline T& operator*() noexcept;
  inline const T& operator*() const noexcept;
  inline T* operator->() noexcept;
  inline T const* operator->() const noexcept;

  friend inline void swap(FastPimpl& a, FastPimpl& b) {
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
inline FastPimpl<T, Size, Align>::FastPimpl(Args&& ... args) noexcept(std::is_nothrow_constructible_v<T, Args...>) {
  static_assert(sizeof(T) <= Size);
  static_assert(alignof(T) == Align);
  new(this->storage) T(std::forward<Args>(args)...);
}

template<class T, std::size_t Size, std::size_t Align>
inline FastPimpl<T, Size, Align>::~FastPimpl() /*noexcept(std::is_nothrow_destructible_v<T>)*/ {
  reinterpret_cast<T*>(this->storage)->~T();
}

template<class T, std::size_t Size, std::size_t Align>
inline FastPimpl<T, Size, Align>::FastPimpl(const FastPimpl<T, Size, Align>& pimpl)
noexcept(std::is_nothrow_copy_constructible_v<T>) {
  new(this->storage) T(*pimpl);
}

template<class T, std::size_t Size, std::size_t Align>
inline FastPimpl<T, Size, Align>::FastPimpl(FastPimpl<T, Size, Align>&& pimpl)
noexcept(std::is_nothrow_move_constructible_v<T>) {
  new(this->storage) T(std::move(*pimpl));
}

template<class T, std::size_t Size, std::size_t Align>
inline FastPimpl<T, Size, Align>& FastPimpl<T, Size, Align>::operator=(const FastPimpl<T, Size, Align>& pimpl)
noexcept(std::is_nothrow_copy_assignable_v<T>) {
  if (this == &pimpl) {
    return *this;
  }
  **this = *pimpl;
  return *this;
}

template<class T, std::size_t Size, std::size_t Align>
inline FastPimpl<T, Size, Align>& FastPimpl<T, Size, Align>::operator=(FastPimpl<T, Size, Align>&& pimpl)
noexcept(std::is_nothrow_move_assignable_v<T>) {
  **this = std::move(*pimpl);
  return *this;
}

template<class T, std::size_t Size, std::size_t Align>
inline T& FastPimpl<T, Size, Align>::operator*() noexcept {
  return *reinterpret_cast<T*>(this->storage);
}

template<class T, std::size_t Size, std::size_t Align>
inline const T& FastPimpl<T, Size, Align>::operator*() const noexcept {
  return *reinterpret_cast<const T*>(this->storage);
}

template<class T, std::size_t Size, std::size_t Align>
T const* FastPimpl<T, Size, Align>::operator->() const noexcept {
  return &**this;
}

template<class T, std::size_t Size, std::size_t Align>
T* FastPimpl<T, Size, Align>::operator->() noexcept {
  return &**this;
}
//endregion
