//
// Created by jungletryne on 02.04.2020.
//
#pragma once

#include <iostream>
#include <vector>
#include <queue>

const int INF = 1e9;

int FindShortestPaidPath(const std::vector<std::vector<std::pair<size_t, int>>>& graph, size_t from, size_t to, size_t limit);

int SolveProblem(const std::vector<std::vector<std::pair<size_t, int>>>& graph, size_t limit, size_t rickFrom, size_t rickTo);
