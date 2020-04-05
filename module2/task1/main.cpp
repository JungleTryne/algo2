#include "task1.h"

int main() {
    size_t aBottles = 0, bBottles = 0, graphSize = 0, start = 0, finish = 0;
    std::cin >> aBottles >> bBottles >> graphSize >> start >> finish;
    std::cout << SolveProblem(graphSize, aBottles, bBottles, start, finish);
    return 0;
}
