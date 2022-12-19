/// @file tuple_element_index.hpp
#pragma once
#include <tuple>
#include <type_traits>
#include <variant>

namespace iris::detail {
  // tuple_element_index
  // https://github.com/llvm/llvm-project/blob/main/libcxx/include/__tuple/tuple_element.h
  // https://github.com/boostorg/hana/blob/944f7177e12c0546b91f58e5f80f054907225739/include/boost/hana/detail/type_at.hpp

  template <std::size_t I, class T>
  struct indexed {};

  template <class Seq, class... Ts>
  struct indexer;

  template <std::size_t... Is, class... Ts>
  struct indexer<std::index_sequence<Is...>, Ts...> : indexed<Is, Ts>... {};

  template <class T, std::size_t I>
  std::integral_constant<std::size_t, I>
  get_index(const indexed<I, T>&); // undefined

  template <class T, class Tuple>
  struct tuple_element_index;

  template <class T, class Tuple>
  struct tuple_element_index<T, const Tuple> : tuple_element_index<T, Tuple> {};

  template <class T, class... Ts>
  struct tuple_element_index<T, std::tuple<Ts...>>
    : decltype(get_index<T>(indexer<std::index_sequence_for<Ts...>, Ts...>{})) {
  };

  template <class T, class Tuple>
  inline constexpr std::size_t tuple_element_index_v =
    tuple_element_index<T, Tuple>::value;

  // variant_alternative_index

  template <class T, class Variant>
  struct variant_alternative_index;

  template <class T, class Variant>
  struct variant_alternative_index<T, const Variant>
    : variant_alternative_index<T, Variant> {};

  template <class T, class... Ts>
  struct variant_alternative_index<T, std::variant<Ts...>>
    : decltype(get_index<T>(indexer<std::index_sequence_for<Ts...>, Ts...>{})) {
  };

  template <class T, class Variant>
  inline constexpr std::size_t variant_alternative_index_v =
    variant_alternative_index<T, Variant>::value;
} // namespace iris::detail

namespace iris {
  using detail::tuple_element_index, detail::tuple_element_index_v;
  using detail::variant_alternative_index, detail::variant_alternative_index_v;
} // namespace iris
