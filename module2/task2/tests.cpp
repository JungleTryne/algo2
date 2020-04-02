//
// Created by jungletryne on 02.04.2020.
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task2.h"

TEST_CASE("Test1") {
    size_t limit = 2;
    size_t start = 4;
    size_t finish = 1;

    vector<vector<pair<size_t,int>>> graph = {
            {std::make_pair(1, 6)},
            {std::make_pair(4, 7)},
            {std::make_pair(4, 1)},
            {std::make_pair(0, 9), std::make_pair(4, 3), std::make_pair(2, 2)},
            {std::make_pair(0, 1)}
    };

    int answer = solveProblem(graph, limit, start, finish);
    REQUIRE(answer == 4);
}

TEST_CASE("Test2") {
    size_t limit = 1;
    size_t start = 1;
    size_t finish = 3;

    vector<vector<pair<size_t,int>>> graph = {
            {std::make_pair(1, 4)},
            {std::make_pair(2, 5)},
            {std::make_pair(0, 6)}
    };

    int answer = solveProblem(graph, limit, start, finish);
    REQUIRE(answer == 4);
}

TEST_CASE("Test3") {
    size_t limit = 1;
    size_t start = 0;
    size_t finish = 3;

    vector<vector<pair<size_t,int>>> graph = {
            {std::make_pair(3, 5), std::make_pair(1, 1)},
            {std::make_pair(2, 1)},
            {std::make_pair(3, 1)},
            {}
    };

    int answer = solveProblem(graph, limit, start, finish);
    REQUIRE(answer == 5);
}
