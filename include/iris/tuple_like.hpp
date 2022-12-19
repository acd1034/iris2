/// @file tuple_like.hpp
#pragma once
#include <tuple>
#include <type_traits>
#include <utility>

namespace iris::_tuple_like {
  // tuple_like
  // https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2165r3.pdf

  template <auto>
  void get(auto&) = delete;
  template <auto>
  void get(const auto&) = delete;

  template <class T, class = std::make_index_sequence<std::tuple_size_v<T>>,
            class = void>
  struct has_tuple_element : std::false_type {};

  template <class T, std::size_t... Is>
  struct has_tuple_element<
    T, std::index_sequence<Is...>,
    std::void_t<typename std::tuple_element<Is, T>::type...>> : std::true_type {
  };

  template <class T, class = std::make_index_sequence<std::tuple_size_v<T>>,
            class = void>
  struct has_unqualified_get : std::false_type {};

  template <class T, std::size_t... Is>
  struct has_unqualified_get<
    T, std::index_sequence<Is...>,
    std::void_t<decltype(get<Is>(std::declval<T&>()))...>> : std::true_type {};

  template <class T, class = void>
  struct is_tuple_like : std::false_type {};

  template <class T>
  struct is_tuple_like<T&, void> : is_tuple_like<T> {};

  template <class T>
  struct is_tuple_like<T&&, void> : is_tuple_like<T> {};

  template <class T>
  struct is_tuple_like<T, std::void_t<decltype(std::tuple_size<T>::value)>>
    : std::conjunction<has_tuple_element<T>, has_unqualified_get<T>> {};

  template <class T>
  inline constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

  template <class T>
  concept tuple_like = is_tuple_like_v<std::remove_cvref_t<T>>;
} // namespace iris::_tuple_like

namespace iris {
  using _tuple_like::is_tuple_like, _tuple_like::is_tuple_like_v,
    _tuple_like::tuple_like;
} // namespace iris
