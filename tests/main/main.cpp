#include <catch2/catch_test_macros.hpp>
#include <iris/fundamental.hpp>
#include <iris/tuple_element_index.hpp>
#include <iris/tuple_like.hpp>
// for test
#include <array>
#include <string>

TEST_CASE("main", "[main][similar_to]") {
  CHECK(iris::similar_to<const int&, int>);
}

TEST_CASE("main", "[main][tuple_element_index]") {
  // clang-format off
  CHECK(iris::tuple_element_index_v<int, std::tuple<int, double, std::string>> == 0);
  CHECK(iris::tuple_element_index_v<int, const std::tuple<int, double, std::string>> == 0);
  CHECK(iris::tuple_element_index_v<double, std::tuple<int, double, std::string>> == 1);
  CHECK(iris::tuple_element_index_v<std::string, std::tuple<int, double, std::string>> == 2);
  CHECK(iris::variant_alternative_index_v<int, std::variant<int, double, std::string>> == 0);
  CHECK(iris::variant_alternative_index_v<double, std::variant<int, double, std::string>> == 1);
  CHECK(iris::variant_alternative_index_v<std::string, std::variant<int, double, std::string>> == 2);
  // clang-format on
}

TEST_CASE("main", "[main][tuple_like]") {
  // clang-format off
  CHECK(iris::tuple_like<std::pair<int, double>>);
  CHECK(iris::tuple_like<std::pair<int, double>&>);
  CHECK(iris::tuple_like<std::pair<int, double>&&>);
  CHECK(iris::tuple_like<const std::pair<int, double>>);
  CHECK(iris::tuple_like<const std::pair<int, double>&>);
  CHECK(iris::tuple_like<const std::pair<int, double>&&>);
  CHECK(iris::tuple_like<std::tuple<int, double, std::string>>);
  CHECK(iris::tuple_like<std::array<int, 7>>);
  CHECK(not iris::tuple_like<std::string>);
  // clang-format on
}
