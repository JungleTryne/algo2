#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task4.h"

TEST_CASE("Test 1") {
    std::vector<size_t> parents = {0, 0, 1};
    LCA lca(parents);
    REQUIRE(lca.getLCA(1, 2) == 1);
    REQUIRE(lca.getLCA(0, 1) == 0);
}

TEST_CASE("Test 2") {
    std::vector<size_t> parents = {0, 0, 0};
    LCA lca(parents);
    REQUIRE(lca.getLCA(1, 2) == 0);
}

TEST_CASE("Test 3") {
    std::vector<size_t> parents = {0, 0, 0, 1, 1, 2, 2};
    LCA lca(parents);
    REQUIRE(lca.getLCA(3, 4) == 1);
    REQUIRE(lca.getLCA(5, 6) == 2);
}