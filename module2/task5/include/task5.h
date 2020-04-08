//
// Created by jungletryne on 08.04.2020.
//

#pragma once

#include <iostream>
#include <vector>

const double INF = 1000000.0;

struct Edge {
    size_t from;
    size_t to;
    double rate;
    double commission;

    Edge(size_t from, size_t to, double rate, double commission);
    [[nodiscard]] double cost(double currentSum) const;
};

bool CanGetMoreMoney(const std::vector<Edge>& graph, size_t vertexCount, size_t from, double initialCash);
