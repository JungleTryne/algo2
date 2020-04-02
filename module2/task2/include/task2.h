//
// Created by jungletryne on 02.04.2020.
//
#pragma once

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::string;
using std::queue;
using std::pair;

const int INF = 1e9;

int findShortestPaidPath(const vector<vector<pair<size_t, int>>>& graph, size_t from, size_t to, size_t limit);

int solveProblem(const vector<vector<pair<size_t, int>>>& graph, size_t limit, size_t rickFrom, size_t rickTo);
