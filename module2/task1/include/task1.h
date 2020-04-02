#pragma once

#include <iostream>
#include <vector>

const int INF = 1e9;

using std::vector;
using std::pair;
using std::cin;
using std::cout;

struct Edge {
    int from;
    int to;
    int cost;
};

int getAliveProbability(const vector<Edge>& graph, size_t vertexCount, int from, int to);

void generateGraph(vector<Edge>& graph, size_t graphSize, size_t aBottles, size_t bBottles);

int solveProblem(size_t graphSize, size_t aBottles, size_t bBottles, size_t start, size_t finish);
