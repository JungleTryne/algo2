#include "task2.h"

int main() {
    size_t graphSize = 0;
    size_t edgesCount = 0;
    std::cin >> graphSize >> edgesCount;

    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph;
    for (size_t i = 0; i < edgesCount; ++i) {
        size_t from = 0;
        size_t to = 0;
        size_t value = 0;
        std::cin >> from >> to >> value;
        graph.emplace_back(value, std::make_pair(from-1, to-1));
    }
    std::cout << GetMST(graphSize, graph) << std::endl;
    return 0;
}
