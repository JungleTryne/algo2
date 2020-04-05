#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "task4.h"

TEST_CASE("Test1") {
    size_t vertexCount = 3;
    std::vector<std::string> inputMatrix = {
            "010",
            "001",
            "000"
    };
    std::vector<std::string> outputMatrix;
    SolveProblem(vertexCount, inputMatrix, outputMatrix);

    std::vector<std::string> answerMatrix = {
            "011",
            "001",
            "000"
    };
    REQUIRE(outputMatrix == answerMatrix);
}

TEST_CASE("Test2") {
    size_t vertexCount = 3;
    std::vector<std::string> inputMatrix = {
            "100",
            "010",
            "001"
    };
    std::vector<std::string> outputMatrix;
    SolveProblem(vertexCount, inputMatrix, outputMatrix);

    std::vector<std::string> answerMatrix = {
            "100",
            "010",
            "001"
    };
    REQUIRE(outputMatrix == answerMatrix);
}

TEST_CASE("Test3") {
    size_t vertexCount = 3;
    std::vector<std::string> inputMatrix = {
            "010",
            "001",
            "100"
    };
    std::vector<std::string> outputMatrix;
    SolveProblem(vertexCount, inputMatrix, outputMatrix);

    std::vector<std::string> answerMatrix = {
            "111",
            "111",
            "111"
    };
    REQUIRE(outputMatrix == answerMatrix);
}