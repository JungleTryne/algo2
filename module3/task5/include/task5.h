#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

//Алгоритм нахождения увеличивающего пути в графе
bool GetAdditivePath(std::vector<bool>& visited,
                     std::vector<int>& prefixFlow,
                     std::vector<size_t>& parent,
                     std::vector<size_t>& distance,
                     const std::vector<std::vector<std::pair<int, int>>>& capacity,
                     const std::vector<std::vector<std::pair<int, int>>>& currentFlow,
                     size_t graphSize, size_t from, size_t to);


//Функция нахождения путей для героев
void GetPaths(std::vector<std::vector<std::pair<int, int>>> currentFlow, size_t from, size_t to,
              std::vector<size_t>& firstPath, std::vector<size_t>& secondPath);


//Алгоритм нахождения максимального потока в графе
//В firstPath и secondPath записываются соответствующие пути, по которым должны пойти герои задачи
size_t GetMaxFlow(const std::vector<std::vector<std::pair<int, int>>>& capacity,
                  std::vector<std::vector<std::pair<int, int>>>& currentFlow, size_t graphSize, size_t from, size_t to,
                  std::vector<size_t>& firstPath, std::vector<size_t>& secondPath);
