#pragma once

#include <type_traits>

namespace stm32cubemx_helper {
namespace {
namespace detail {

template <class T, T *K, class V> V *&context() {
  static V *context = nullptr;
  return context;
}

} // namespace detail
} // namespace

template <class T, T *K, class V> V *get_context() {
  return detail::context<T, K, V>();
}

template <class T, T *K, class V> void set_context(V *value) {
  detail::context<T, K, V>() = value;
}

namespace detail {}

#if __cplusplus >= 201703L

template <auto *K, class V> V *get_context() {
  return get_context<std::remove_pointer_t<decltype(K)>, K, V>();
}

template <auto *K, class V> void set_context(V *value) {
  set_context<std::remove_pointer_t<decltype(K)>, K, V>(value);
}

#endif

} // namespace stm32cubemx_helper
