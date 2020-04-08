//
// Created by jungletryne on 08.04.2020.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task5.h"

TEST_CASE("Test1") {
    size_t vertexCount = 3;
    size_t start = 0;
    double initialCash = 10.0;
    std::vector<Edge> graph = {
            Edge(0, 1, 1.0, 1.0),
            Edge(1, 0, 1.0, 1.0),
            Edge(1, 2, 1.1, 1.0),
            Edge(2, 1, 1.1, 1.0)
    };
    bool answer = CanGetMoreMoney(graph, vertexCount, start, initialCash);
    REQUIRE(!answer);
}

TEST_CASE("Test2") {
    size_t vertexCount = 2;
    size_t start = 0;
    double initialCash = 10.0;
    std::vector<Edge> graph = {
            Edge(0, 1, 1.0, 1.0),
            Edge(1, 0, 1.0, 1.0),
            Edge(1, 1, 1.1, 0),
            Edge(1, 1, 1.1, 0)
    };
    bool answer = CanGetMoreMoney(graph, vertexCount, start, initialCash);
    REQUIRE(answer);
}
