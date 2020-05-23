#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task2.h"
TEST_CASE("Simple Test") {
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph = {
            std::make_pair(1231232, std::make_pair(0,1)),
    };
    size_t result = GetMST(2, graph);
    REQUIRE(result == 1231232);
}

TEST_CASE("Harder one") {
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph = {
            std::make_pair(3, std::make_pair(0,1)),
            std::make_pair(4, std::make_pair(0,2)),
            std::make_pair(5, std::make_pair(1,2))
    };
    size_t result = GetMST(3, graph);
    REQUIRE(result == 7);
}

TEST_CASE("Final Test") {
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph = {
            std::make_pair(2, std::make_pair(0,1)),
            std::make_pair(2, std::make_pair(1,2)),
            std::make_pair(2, std::make_pair(2,3))
    };
    size_t result = GetMST(4, graph);
    REQUIRE(result == 6);
}