#pragma once

#include <iostream>
#include <vector>

const int INF = 1e9;

struct Edge {
    int from;
    int to;
    int cost;
    Edge(int from, int to, int cost);
};

int GetAliveProbability(const std::vector<Edge>& graph, size_t vertexCount, int from, int to);

void GenerateGraph(std::vector<Edge>& graph, size_t graphSize, size_t aBottles, size_t bBottles);

int SolveProblem(size_t aBottles, size_t bBottles, size_t graphSize, size_t start, size_t finish);
