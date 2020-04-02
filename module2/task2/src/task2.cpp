//Данила Мишин, Б05-927
//Решение задачи B "Rick for the weekend"

#include "task2.h"

//Функция нахождения нахождении минимального по стоимости путя
//Используется алгоритм Форда-Беллмана
int findShortestPaidPath(const vector<vector<pair<size_t, int>>>& graph, size_t from, size_t to, size_t limit) {
    vector<size_t> dynamicCost(graph.size(), INF);
    vector<size_t> stepsMade(graph.size(), -1); //Сколько шагов было сделано, чтобы добиться результата dynamicCost[i]
    vector<bool> isVertexInQueue(graph.size(), false);

    dynamicCost[from] = 0; //Нам нисколько не стоит попасть в старт
    stepsMade[from] = 0;
    queue<size_t> vertexQueue;
    vertexQueue.push(from);

    while (!vertexQueue.empty()) {
        size_t currentVertex = vertexQueue.front();
        vertexQueue.pop();
        isVertexInQueue[currentVertex] = false;
        for (size_t i = 0; i < graph[currentVertex].size(); ++i) {
            size_t goingToVertex = graph[currentVertex][i].first;
            int cost = graph[currentVertex][i].second;
            if (dynamicCost[currentVertex] + cost < dynamicCost[goingToVertex] && stepsMade[currentVertex] < limit) {
                dynamicCost[goingToVertex] = dynamicCost[currentVertex] + cost;
                stepsMade[goingToVertex] = stepsMade[currentVertex] + 1;
                if (!isVertexInQueue[goingToVertex]) {
                    vertexQueue.push(goingToVertex);
                    isVertexInQueue[goingToVertex] = true;
                }
            }
        }
    }

    return (dynamicCost[to] < INF ? dynamicCost[to] : -1);
}

//Функция для решения задачи. Вынесена отдельно для тестирования
int solveProblem(const vector<vector<pair<size_t, int>>>& graph, size_t limit, size_t rickFrom, size_t rickTo) {
    return findShortestPaidPath(graph, rickFrom-1, rickTo-1, limit);
}
