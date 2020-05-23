#include "task4.h"

//Структура, которая позволяет хэшировать пары для использования их в unordered_map
template<typename T1, typename T2>
size_t pair_hash::operator() (const std::pair<T1,T2> &pair) const {
    auto h1 = std::hash<T1>{}(pair.first);
    auto h2 = std::hash<T2>{}(pair.second);
    return h1 ^ h2;
}

//Алгоритм Куна для нахождения максимального паросочетания
bool KuhnAlgorithm(size_t from, const std::vector<std::vector<size_t>>& graph, std::vector<long long>& pairs,
        std::vector<bool>& visited)
{
    if (visited[from]) {
        return false;
    }
    visited[from] = true;
    for (size_t i = 0; i < graph[from].size(); ++i) {
        size_t to = graph[from][i];
        if (pairs[to] == -1) {
            pairs[to] = from;
            return true;
        } else {
            if (KuhnAlgorithm(pairs[to], graph, pairs, visited)) {
                pairs[to] = from;
                return true;
            }
        }
    }
    return false;
}

//Функция для преобразования моста в граф
void GetBipartiteGraph(const std::vector<std::string>& bridge, std::vector<std::pair<size_t, size_t>>& firstHalf,
        std::vector<std::pair<size_t, size_t>>& secondHalf, std::vector<std::vector<size_t>>& graph)
{

    std::unordered_map<std::pair<size_t, size_t>, size_t, pair_hash> secondHalfIndexer = {};

    for (size_t i = 0; i < bridge.size(); ++i) {
        for (size_t j = 0; j < bridge[i].size(); ++j) {
            if (bridge[i][j] == '*') {
                if ((i + j) % 2 == 0) {
                    firstHalf.emplace_back(i, j);
                } else {
                    secondHalf.emplace_back(i, j);
                    secondHalfIndexer[std::make_pair(i,j)] = secondHalf.size() - 1;
                }
            }
        }
    }

    graph = std::vector<std::vector<size_t>>(firstHalf.size(), std::vector<size_t>(0));

    for (size_t i = 0; i < firstHalf.size(); ++i) {
        size_t y = firstHalf[i].first;
        size_t x = firstHalf[i].second;
        if (x > 0 && bridge[y][x-1] == '*') {
            auto coordinate = std::make_pair(y,x-1);
            size_t index = secondHalfIndexer[coordinate];
            graph[i].push_back(index);
        }
        if (x < bridge[y].size()-1 && bridge[y][x+1] == '*') {
            graph[i].push_back(secondHalfIndexer[std::make_pair(y, x+1)]);
        }
        if (y > 0 && bridge[y-1][x] == '*') {
            graph[i].push_back(secondHalfIndexer[std::make_pair(y-1, x)]);
        }
        if (y < bridge.size()-1 && bridge[y+1][x] == '*') {
            graph[i].push_back(secondHalfIndexer[std::make_pair(y+1, x)]);
        }
    }
}

//Функция нахождения стоимости починки моста
long long FixBridge(const std::vector<std::string>& bridge, long long priceA, long long priceB) {
    if (2*priceB <= priceA) {
        long long counter = 0;
        for (const auto &row : bridge) {
            for (auto i : row) {
                if (i == '*') {
                    counter += 1;
                }
            }
        }
        return counter * priceB;
    }
    std::vector<std::pair<size_t, size_t>> firstHalf;
    std::vector<std::pair<size_t, size_t>> secondHalf;
    std::vector<std::vector<size_t>> graph;

    GetBipartiteGraph(bridge, firstHalf, secondHalf, graph);

    if (firstHalf.empty()) {
        return static_cast<long long>(secondHalf.size()) * priceB;
    }
    if (secondHalf.empty()) {
        return static_cast<long long>(firstHalf.size()) * priceB;
    }

    size_t firstHalfSize = firstHalf.size();
    size_t secondHalfSize = secondHalf.size();
    std::vector<long long> pairs(secondHalfSize, -1);
    std::vector<bool> visited(firstHalfSize, false);

    for (size_t i = 0; i < firstHalfSize; ++i) {
        KuhnAlgorithm(i, graph, pairs, visited);
        visited.assign(firstHalfSize, false);
    }

    size_t twoBlockCount = 0;
    for (long long pair : pairs) {
        if (pair != -1) {
            twoBlockCount++;
        }
    }

    return twoBlockCount * priceA + (firstHalfSize + secondHalfSize - twoBlockCount * 2) * priceB;
}
