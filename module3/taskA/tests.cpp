#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task1.h"

TEST_CASE("Simple Test") {
    std::vector<std::vector<std::pair<size_t, size_t>>> graph = {
            {std::make_pair(1, 1231232)},
            {std::make_pair(0, 1231232)}
    };
    size_t result = GetMST(graph);
    REQUIRE(result == 1231232);
}

TEST_CASE("Harder one") {
    std::vector<std::vector<std::pair<size_t, size_t>>> graph = {
            {std::make_pair(1, 3), std::make_pair(2, 4)},
            {std::make_pair(2, 5), std::make_pair(0, 3)},
            {std::make_pair(1, 5), std::make_pair(0, 4)},
    };
    size_t result = GetMST(graph);
    REQUIRE(result == 7);
}

TEST_CASE("Final Test") {
    std::vector<std::vector<std::pair<size_t, size_t>>> graph = {
            {std::make_pair(1, 2)},
            {std::make_pair(2, 2), std::make_pair(0, 2)},
            {std::make_pair(3, 2), std::make_pair(1, 2)},
            {std::make_pair(2, 2)},
    };
    size_t result = GetMST(graph);
    REQUIRE(result == 6);
}