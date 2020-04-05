#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "task3.h"

TEST_CASE("Test1") {
    size_t vertexCount = 5;
    size_t rickFrom = 0;
    size_t rickTo = 2;
    std::vector<Edge> graph = {
            Edge(0, 1, 20),
            Edge(2, 3, 10),
            Edge(0, 4, 37),
            Edge(0, 2, 50),
            Edge(1, 2, 20),
            Edge(3, 4, 92),
            Edge(0, 3, 67)
    };
    double answer = SolveProblem(graph, vertexCount, rickFrom, rickTo);
    REQUIRE(answer - 0.36 < 0.0000001);
}

TEST_CASE("Test2") {
    size_t vertexCount = 3;
    size_t rickFrom = 0;
    size_t rickTo = 2;
    std::vector<Edge> graph = {
            Edge(0, 1, 50),
            Edge(1, 2, 50),
            Edge(0, 2, 100),
    };
    double answer = SolveProblem(graph, vertexCount, rickFrom, rickTo);
    REQUIRE(answer - 0.75 < 0.0000001);
}

TEST_CASE("Test3") {
    size_t vertexCount = 4;
    size_t rickFrom = 0;
    size_t rickTo = 3;
    std::vector<Edge> graph = {
            Edge(0, 1, 50),
            Edge(1, 3, 25),
            Edge(0, 2, 26),
            Edge(2, 3, 50),
    };
    double answer = SolveProblem(graph, vertexCount, rickFrom, rickTo);
    REQUIRE(answer - 0.625 < 0.0000001);
}
