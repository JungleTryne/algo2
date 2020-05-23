#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "task2.h"

TEST_CASE("Test1") {
    std::vector<size_t> initial_state = {0, 0, 0, 0, 0};
    SegmentTree tree(initial_state, 5);
    tree.updateTree(0, 4, 5);
    REQUIRE(tree.getMax(0, 4) >= 5);
}

TEST_CASE("Test2") {
    std::vector<size_t> initial_state = {0, 0, 0, 0, 0};
    SegmentTree tree(initial_state, 5);
    tree.updateTree(0, 4, 1);
    tree.updateTree(1, 4, 2);
    REQUIRE(tree.getMax(3, 4) < 5);
}

TEST_CASE("Test3") {
    std::vector<size_t> initial_state = {0, 0, 0, 0, 0};
    SegmentTree tree(initial_state, 5);
    tree.updateTree(0, 1, 5);
    REQUIRE(tree.getMax(0, 4) >= 5);
}