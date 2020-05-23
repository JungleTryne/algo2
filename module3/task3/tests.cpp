#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task3.h"

TEST_CASE("Test One") {
    std::vector<size_t> prices = {1,3,3};
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> specialOffers = {
            std::make_pair(5, std::make_pair(1,2)),
            std::make_pair(1, std::make_pair(1,0))
    };

    std::vector<std::vector<std::pair<size_t, size_t>>> graph;
    GetBestGraph(prices, specialOffers, graph);
    size_t result = GetMST(graph);
    REQUIRE(result == 5);
}

TEST_CASE("Test Two") {
    std::vector<size_t> prices = {1, 3, 3, 7};
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> specialOffers = {};

    std::vector<std::vector<std::pair<size_t, size_t>>> graph;
    GetBestGraph(prices, specialOffers, graph);
    size_t result = GetMST(graph);
    REQUIRE(result == 16);
}

TEST_CASE("Test Three") {
    std::vector<size_t> prices = {1, 2, 3, 4, 5};
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> specialOffers = {
            std::make_pair(8, std::make_pair(0,1)),
            std::make_pair(10, std::make_pair(0,2)),
            std::make_pair(7, std::make_pair(0,3)),
            std::make_pair(15, std::make_pair(0,4))
    };

    std::vector<std::vector<std::pair<size_t, size_t>>> graph;
    GetBestGraph(prices, specialOffers, graph);
    size_t result = GetMST(graph);
    REQUIRE(result == 18);
}