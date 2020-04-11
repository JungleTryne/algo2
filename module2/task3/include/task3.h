#pragma once

#include <iostream>
#include <vector>

struct Edge {
    size_t from;
    size_t to;
    double cost;
    Edge(size_t from, size_t to, double cost);
    Edge(const Edge& other);
};

double GetAliveProb(const std::vector<Edge>& graph, size_t vertexCount, size_t from, size_t to);

double SolveProblem(const std::vector<Edge>& graph, size_t vertexCount, size_t from, size_t to);
