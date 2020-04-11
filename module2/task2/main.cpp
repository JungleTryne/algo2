#include <iostream>
#include <vector>

#include "task2.h"

int main() {
    int vertexCount = 0;
    int edgeCount = 0;
    int limit = 0;
    int rickFrom = 0;
    int rickTo = 0;
    std::cin >> vertexCount >> edgeCount >> limit >> rickFrom >> rickTo;

    std::vector<std::vector<std::pair<size_t,int>>> graph(vertexCount);
    for (int i = 0; i < edgeCount; ++i) {
        int from = 0, to = 0, cost = 0;
        std::cin >> from >> to >> cost;
        graph[from-1].push_back(std::make_pair(to-1, cost));
    }

    std::cout << SolveProblem(graph, limit, rickFrom, rickTo);
    return 0;
}
