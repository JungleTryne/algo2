//Мишин Данила, Б05-927
//Решение задачи А - Who let the Rick out

#include "task1.h"

//Функция вычисления количества бутылок, которые он отдаст
//Используется модифицированный алгоритм Форда-Беллмана
int getAliveProbability(const vector<Edge>& graph, size_t vertexCount, int from, int to) {
    vector<int> dynamicCosts(vertexCount, INF);
    dynamicCosts[from] = 0;

    while (true) {
        bool hasSomethingChanged = false;
        for (auto vertex : graph) {
            int fromCurrent = vertex.from;
            int toCurrent = vertex.to;
            if (dynamicCosts[toCurrent] > dynamicCosts[fromCurrent] + vertex.cost) {
                dynamicCosts[toCurrent] = dynamicCosts[fromCurrent] + vertex.cost;
                hasSomethingChanged = true;
            }
        }
        if (!hasSomethingChanged) {
            break;
        }
    }
    return dynamicCosts[to];
}

//Функция генерации графа телепортов во вселенной
void generateGraph(vector<Edge>& graph, size_t graphSize, size_t aBottles, size_t bBottles) {
    for (size_t i = 0; i < graphSize; ++i) {
        Edge edge(i, (i + 1) % graphSize, aBottles); //Первый способ телепортации
        Edge edgeSecond(i, (i*i + 1) % graphSize, bBottles); //Второй способ телепортации
        graph.push_back(edge);
        graph.push_back(edgeSecond);
    }
}

//Функция решения задачи. Вынесена отдельно для выполнения тестов
int solveProblem(size_t aBottles, size_t bBottles, size_t graphSize, size_t start, size_t finish) {
    vector<Edge> graph;
    generateGraph(graph, graphSize, aBottles, bBottles);
    int answer = getAliveProbability(graph, graphSize, start, finish);
    return answer;
}

Edge::Edge(int from, int to, int cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
}
