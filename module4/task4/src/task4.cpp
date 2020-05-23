#include "task4.h"

LCA::LCA(const std::vector<size_t> &parents) :
        parents(parents),
        graph(std::vector<std::vector<size_t>>(parents.size(), std::vector<size_t>(0))),
        dynamic(std::vector<std::vector<size_t>>(parents.size(),
        std::vector<size_t>(floor(log2(this->graph.size())) + 1, 0))),
        timeIn(parents.size()),
        timeOut(parents.size()),
        log(floor(log2(this->graph.size())) + 1)
{
    for (size_t i = 1; i < this->parents.size(); ++i) {
        graph[this->parents[i]].push_back(i);
    }

    size_t timer = 0;
    this->getDepths(0, 0, timer);

    for (size_t i = 0; i < this->graph.size(); ++i) {
        dynamic[i][0] = this->parents[i];
    }

    for (size_t i = 1; i < log; ++i) {
        for (size_t j = 1; j < this->graph.size(); ++j) {
            dynamic[j][i] = dynamic[dynamic[j][i - 1]][i - 1];
        }
    }
}

//DFSом проходимся по дереву и сохраняем времена входа и выхода из вершин
void LCA::getDepths(size_t vertex, size_t depth, size_t &counter) {
    timeIn[vertex] = counter;
    ++counter;
    for (size_t child : this->graph[vertex]) {
        getDepths(child, depth + 1, counter);
    }
    ++counter;
    timeOut[vertex] = counter;
}

//Используем метод двоичного подъема
size_t LCA::getLCA(size_t firstVertex, size_t secondVertex) {
    if (upper(firstVertex, secondVertex)) {
        return firstVertex;
    }
    if (upper(secondVertex, firstVertex)) {
        return secondVertex;
    }
    for (auto i = static_cast<long long>(log - 1); i > -1; --i) {
        if (!upper(dynamic[firstVertex][i], secondVertex)) {
            firstVertex = dynamic[firstVertex][i];
        }
    }

    return this->parents[firstVertex];
}

bool LCA::upper(size_t firstVertex, size_t secondVertex) {
    return timeIn[firstVertex] <= timeIn[secondVertex] && timeOut[firstVertex] >= timeOut[secondVertex];
}
