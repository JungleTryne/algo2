// Мишин Данила, Бо5-927
// Задача E, "Ricked out"
#include "task5.h"

Edge::Edge(size_t from, size_t to, double rate, double commission) {
    this->from = from;
    this->to = to;
    this->rate = rate;
    this->commission = commission;
}

double Edge::cost(double currentSum) const {
    return rate*(currentSum - commission);
}

//Используется модифицированный алгоритм Форда-Беллмана
//Ищем "положительный" цикл в графе
bool CanGetMoreMoney(const std::vector<Edge>& graph, size_t vertexCount, size_t from, double initialCash) {
    std::vector<double> dynamicCosts(vertexCount, 0.0);
    dynamicCosts[from] = initialCash;
    long long x = -1;

    for (size_t i = 0; i < vertexCount; ++i) {
        x = -1;
        for (const auto& edge : graph) {
            size_t currentFrom = edge.from;
            size_t currentTo = edge.to;
            if (dynamicCosts[currentFrom] >= 1e-6) {
                if (dynamicCosts[currentTo] <= edge.cost(dynamicCosts[currentFrom]) - 1e-6) {
                    dynamicCosts[currentTo] = edge.cost(dynamicCosts[currentFrom]);
                    x = currentTo;
                }
            }
        }
    }
    return x != -1;
}
