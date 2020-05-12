#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "task4.h"

TEST_CASE("Test One") {
    std::vector<std::string> bridge = {
            ".**",
            ".*."
    };

    long long answer = FixBridge(bridge, 3, 2);
    REQUIRE(answer == 5);
}

TEST_CASE("Test Two") {
    std::vector<std::string> bridge = {
            "...",
            "...",
            "..."
    };

    long long answer = FixBridge(bridge, 1, 5);
    REQUIRE(answer == 0);
}

TEST_CASE("Test Three") {
    std::vector<std::string> bridge = {
            "***",
            "***",
            "***"
    };

    long long answer = FixBridge(bridge, 1, 5);
    REQUIRE(answer == 9);
}
