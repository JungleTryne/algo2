#include "task1.h"

size_t GetMST(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph) {
    /*
     * graph - неориентированный взвешенный граф, представленный в виде списка смежности
     * graph[i][].first - вторая вершина ребра, соединяющего с вершиной i
     * graph[i][].second - вес ребра
     */

    std::vector<size_t> minimalEdgeCost(graph.size(), 1e12);
    std::vector<size_t> minimalEdgeSecondVertex(graph.size(), -1);
    std::vector<bool> used(graph.size(), false);

    minimalEdgeCost[0] = 0;

    std::set<std::pair<size_t, size_t>> queue;
    queue.insert(std::make_pair(0,0));

    for (size_t i = 0; i < graph.size(); ++i) {
        if (queue.empty()) {
            //Не удалось найти минимальное оставное дерево (граф не связен)
            return -1;
        }
        size_t currentVertex = queue.begin()->second;
        queue.erase(queue.begin());
        used[currentVertex] = true;

        for (size_t j = 0; j < graph[currentVertex].size(); ++j) {
            size_t toVertex = graph[currentVertex][j].first;
            size_t toCost = graph[currentVertex][j].second;
            if (toCost < minimalEdgeCost[toVertex] && !used[toVertex]) {
                queue.erase(std::make_pair(minimalEdgeCost[toVertex], toVertex));
                minimalEdgeCost[toVertex] = toCost;
                minimalEdgeSecondVertex[toVertex] = currentVertex;
                queue.insert(std::make_pair(minimalEdgeCost[toVertex], toVertex));
            }
        }

    }

    size_t cost = 0;
    for (unsigned long i : minimalEdgeCost) {
        cost += i;
    }

    return cost;
}
