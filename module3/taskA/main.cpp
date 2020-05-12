#include "task1.h"

int main() {
    size_t graphSize = 0;
    size_t edgeCount = 0;
    std::cin >> graphSize >> edgeCount;
    std::vector<std::vector<std::pair<size_t, size_t>>> graph(graphSize);
    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from = 0;
        size_t to = 0;
        size_t cost = 0;
        std::cin >> from >> to >> cost;
        graph[from-1].emplace_back(to-1, cost);
        graph[to-1].emplace_back(from-1, cost);
    }
    std::cout << GetMST(graph) << std::endl;
}
