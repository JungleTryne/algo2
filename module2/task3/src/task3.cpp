#include "task3.h"

Edge::Edge(size_t from, size_t to, double cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
}

Edge::Edge(const Edge& other) {
    this->from = other.from;
    this->to = other.to;
    this->cost = other.cost;
}

//Используется алгоритм Форда-Беллмана, при этом во время релаксации мы перемножаем значения, а не складываем, т.к.
//работаем с вероятностями
double GetAliveProb(const std::vector<Edge>& graph, size_t vertexCount, size_t from, size_t to) {
    std::vector<double> dynamicCosts(vertexCount, 0);
    dynamicCosts[from] = 1;

    size_t depth = vertexCount;
    for (size_t i = 0; i < depth; ++i) {
        for (size_t j = 0; j < graph.size(); ++j) {
            int currentFrom = graph[j].from;
            int currentTo = graph[j].to;
            dynamicCosts[currentTo] = std::max(dynamicCosts[currentTo], dynamicCosts[currentFrom] * graph[j].cost);
        }
    }
    return dynamicCosts[to];
}

//Функция решения задачи. Вынесена отдельно для проведения тестов
double SolveProblem(const std::vector<Edge>& graph, size_t vertexCount, size_t from, size_t to) {
    std::vector<Edge> new_graph = graph;
    for(Edge& edge : new_graph) {
        edge.cost = 1 - edge.cost/100;
    }
    return 1 - GetAliveProb(new_graph, vertexCount, from, to);
}