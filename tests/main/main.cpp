#include <catch2/catch_test_macros.hpp>
#include <iris/fundamental.hpp>
#include <iris/tuple_element_index.hpp>

TEST_CASE("main", "[main][similar_to]") {
  CHECK(iris::similar_to<const int&, int>);
}

TEST_CASE("main", "[main][tuple_element_index]") {
  // clang-format off
  CHECK(iris::tuple_element_index_v<int, std::tuple<int, double, std::monostate>> == 0);
  CHECK(iris::tuple_element_index_v<double, std::tuple<int, double, std::monostate>> == 1);
  CHECK(iris::tuple_element_index_v<std::monostate, std::tuple<int, double, std::monostate>> == 2);
  CHECK(iris::variant_alternative_index_v<int, std::variant<int, double, std::monostate>> == 0);
  CHECK(iris::variant_alternative_index_v<double, std::variant<int, double, std::monostate>> == 1);
  CHECK(iris::variant_alternative_index_v<std::monostate, std::variant<int, double, std::monostate>> == 2);
  // clang-format on
}
