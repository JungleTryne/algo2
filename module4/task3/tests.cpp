#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task3.h"

TEST_CASE("Test 1") {
    std::vector<size_t> plot = {1, 2, 3, 4, 5}; //Нам не важен сам RGB, а только яркость цвета
    SegmentTree tree(plot);
    REQUIRE(tree.getMin(0, 4) == 1);
    REQUIRE(tree.getMin(3, 4) == 4);
}

TEST_CASE("Test 2") {
    std::vector<size_t> plot = {0, 1, 2, 3, 4};
    SegmentTree tree(plot);
    tree.updateTree(0, 4, 0);
    tree.updateTree(3, 3, 10);
    REQUIRE(tree.getMin(0, 4) == 0);
    REQUIRE(tree.getMin(3, 3) == 10);
}