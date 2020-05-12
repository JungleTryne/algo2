#include "task3.h"

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

//Используем жадный алгоритм - соединяем все вершины с самой дешевой вершиной
//Потом добавляем ребра специального предложения и находим миностов
void GetBestGraph(const std::vector<size_t>& prices,
                  const std::vector<std::pair<size_t, std::pair<size_t, size_t>>>& specialOffers,
                  std::vector<std::vector<std::pair<size_t, size_t>>>& output)
{
    size_t minVertex = 0; //Вершина с минимальной ценой

    size_t minPrice = prices[minVertex];
    for (size_t i = 0; i < prices.size(); ++i) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
            minVertex = i;
        }
    }

    std::vector<std::vector<std::pair<size_t, size_t>>> outputGraph(prices.size());
    for (size_t i = 0; i < prices.size(); ++i) {
        if (i != minVertex) {
            outputGraph[minVertex].emplace_back(i, minPrice + prices[i]);
            outputGraph[i].emplace_back(minVertex, minPrice + prices[i]);
        }
    }

    for (auto offer : specialOffers) {
        //Первая вершина ребра совпадает?
        if (offer.second.first == minVertex) {
            size_t index = offer.second.second > minVertex ? offer.second.second - 1 : offer.second.second;
            if (offer.first < outputGraph[offer.second.first][index].second) {
                outputGraph[offer.second.first][index] = std::make_pair(offer.second.second, offer.first);
                outputGraph[offer.second.second][0] = std::make_pair(offer.second.first, offer.first);
            } else {
                continue;
            }
        }

        //Вторая вершина ребра совпадает?
        if (offer.second.second == minVertex) {
            size_t index = offer.second.first > minVertex ? offer.second.first - 1 : offer.second.first;
            if (offer.first < outputGraph[offer.second.second][index].second) {
                outputGraph[offer.second.second][index] = std::make_pair(offer.second.first, offer.first);
                outputGraph[offer.second.first][0] = std::make_pair(offer.second.second, offer.first);
            } else {
                continue;
            }
        }
    }

    for (auto offer : specialOffers) {
        if (offer.second.first != minVertex && offer.second.second != minVertex) {
            outputGraph[offer.second.first].emplace_back(offer.second.second, offer.first);
            outputGraph[offer.second.second].emplace_back(offer.second.first, offer.first);
        }
    }
    output = outputGraph;
}
