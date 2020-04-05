#include <iostream>
#include "task4.h"

int main() {
    size_t graphSize = 0;
    std::cin >> graphSize;
    std::vector<std::string> inputMatrix;
    std::string input;

    for(size_t i = 0; i < graphSize; ++i) {
        std::cin >> input;
        inputMatrix.push_back(input);
    }

    std::vector<std::string> outputMatrix;
    SolveProblem(graphSize, inputMatrix, outputMatrix);

    for(const std::string& line : outputMatrix) {
        std::cout << line << std::endl;
    }
    return 0;
}
