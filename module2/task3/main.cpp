#include "task3.h"

int main() {
    size_t graphSize = 0;
    size_t edgeCount = 0;
    size_t rickFrom = 0;
    size_t rickTo = 0;
    std::cin >> graphSize >> edgeCount  >> rickFrom >> rickTo;
    rickFrom--;
    rickTo--;
    std::vector<Edge> graph;
    for (size_t i = 0; i < edgeCount*2; i+=2) {
        size_t from = 0, to = 0;
        double cost = 0;
        std::cin >> from >> to >> cost;
        Edge edge1(from-1, to-1, cost);
        Edge edge2(to-1, from-1, cost);
        graph.push_back(edge1);
        graph.push_back(edge2);
    }
    double answer = SolveProblem(graph, graphSize, rickFrom, rickTo);
    std::cout << answer;
    return 0;
}