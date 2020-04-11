//
// Created by jungletryne on 02.04.2020.
//

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "task1.h"

TEST_CASE("Test1") {
    int answer = SolveProblem(3, 14, 15, 9, 9);
    REQUIRE(answer == 0);
}

TEST_CASE("Test2") {
    int answer = SolveProblem(6, 1, 5, 2, 3);
    REQUIRE(answer == 6);
}

TEST_CASE("Test3") {
    int answer = SolveProblem(6, 1, 5, 2, 1);
    REQUIRE(answer == 2);
}
