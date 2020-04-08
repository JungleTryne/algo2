//
// Created by jungletryne on 08.04.2020.
//
#include "task5.h"

int main() {
    size_t vertexCount = 0;
    size_t edgeCount = 0;
    size_t start = 0;
    double initialCash = 0;
    std::cin >> vertexCount >> edgeCount >> start >> initialCash;
    std::vector<Edge> graph;

    for (size_t i = 0; i < edgeCount; ++i) {
        size_t from = 0;
        size_t to = 0;
        double rateOne = 0;
        double commissionOne = 0;
        double rateTwo = 0;
        double commissionTwo = 0;
        std::cin >> from >> to >> rateOne >> commissionOne >> rateTwo >> commissionTwo;
        graph.emplace_back(from-1, to-1, rateOne, commissionOne);
        graph.emplace_back(to-1, from-1, rateTwo, commissionTwo);
    }
    bool answer = CanGetMoreMoney(graph, vertexCount, start-1, initialCash);
    std::cout << (answer ? "YES" : "NO");
    return 0;
}
