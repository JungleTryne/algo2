#pragma once

#include <cmath>
#include <iostream>
#include <vector>

//Класс для решения задачи RCA
class LCA {
private:
    std::vector<size_t> parents;
    std::vector<std::vector<size_t>> graph;
    std::vector<std::vector<size_t>> dynamic;
    std::vector<size_t> timeIn;
    std::vector<size_t> timeOut;
    size_t log;

    bool upper(size_t firstVertex, size_t secondVertex);
    void getDepths(size_t vertex, size_t depth, size_t &counter);

public:
    explicit LCA(const std::vector<size_t> &parents);
    size_t getLCA(size_t firstVertex, size_t secondVertex);
};