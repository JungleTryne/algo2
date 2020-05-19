#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "task1.h"

TEST_CASE("Test 1") {
    std::vector<int> array = {1, 2, 3, 4, 5};
    SecondStatistics s(array);
    REQUIRE(s.getSecondStatistics(0, 4) == 2);
    REQUIRE(s.getSecondStatistics(3, 4) == 5);
}

TEST_CASE("Test 2") {
    std::vector<int> array = {0, 5, 4, 2, 10};
    SecondStatistics s(array);
    REQUIRE(s.getSecondStatistics(0, 4) == 2);
    REQUIRE(s.getSecondStatistics(3, 4) == 10);
}

TEST_CASE("Test 3") {
    std::vector<int> array = {0, 0, 0, 0, 0, 0, 0, 0};
    SecondStatistics s(array);
    REQUIRE(s.getSecondStatistics(0, 7) == 0);
    REQUIRE(s.getSecondStatistics(3, 6) == 0);
}
