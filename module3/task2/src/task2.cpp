#include "task2.h"

size_t GetMST(size_t graphSize, const std::vector<std::pair<size_t, std::pair<size_t, size_t>>>& constGraph) {
    /*
     * graph - неориентированный взвешенный граф, представленный в виде списка рёбер
     * graph[i].first - цена ребра
     * graph[i].second.first - первая вершина ребра
     * graph[i].second.second - вторая вершина ребра
     * graphSize - количество вершин в графе
     */

    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> graph = constGraph;
    std::sort(graph.begin(), graph.end());
    size_t result = 0;
    std::vector<size_t> mstNumber(graphSize);

    for (size_t i = 0; i < mstNumber.size(); ++i) {
        mstNumber[i] = i;
    }

    for (auto & currentEdge : graph) {
        size_t from = currentEdge.second.first;
        size_t to = currentEdge.second.second;
        size_t value = currentEdge.first;
        if (mstNumber[from] != mstNumber[to]) {
            result += value;
            size_t oldNumber = mstNumber[to];
            size_t newNumber = mstNumber[from];
            for (size_t j = 0; j < graphSize; ++j) {
                if (mstNumber[j] == oldNumber) {
                    mstNumber[j] = newNumber;
                }
            }
        }
    }
    return result;
}

