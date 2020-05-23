#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task5.h"

TEST_CASE("Test 1") {
    std::vector<std::vector<std::pair<int, int>>> capacity = {
            {std::make_pair(1, 1), std::make_pair(2, 1)},
            {std::make_pair(2, 1), std::make_pair(0, 0)},
            {std::make_pair(1, 0), std::make_pair(0, 0)}
    };
    std::vector<std::vector<std::pair<int, int>>> currentFlow = {
        {std::make_pair(1, 0), std::make_pair(2, 0)},
        {std::make_pair(2, 0), std::make_pair(0, 0)},
        {std::make_pair(1, 0), std::make_pair(0, 0)}
    };
    std::vector<size_t> firstPath;
    std::vector<size_t> secondPath;

    size_t flow = GetMaxFlow(capacity, currentFlow, 3, 0, 2, firstPath, secondPath);

    REQUIRE(flow > 1);
}

TEST_CASE("Test 2") {
    std::vector<std::vector<std::pair<int, int>>> capacity = {
            {std::make_pair(1, 1)},
            {std::make_pair(0, 0)},
    };
    std::vector<std::vector<std::pair<int, int>>> currentFlow = {
            {std::make_pair(1, 0)},
            {std::make_pair(0, 0)},
    };
    std::vector<size_t> firstPath;
    std::vector<size_t> secondPath;

    size_t flow = GetMaxFlow(capacity, currentFlow, 2, 0, 1, firstPath, secondPath);

    REQUIRE(flow <= 1);
}