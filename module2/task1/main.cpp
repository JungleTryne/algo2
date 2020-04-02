#include "task1.h"

int main() {
    size_t aBottles = 0, bBottles = 0, graphSize = 0, start = 0, finish = 0;
    cin >> aBottles >> bBottles >> graphSize >> start >> finish;
    cout << solveProblem(graphSize, aBottles, bBottles, start, finish);
    return 0;
}
