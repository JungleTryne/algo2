#pragma once

#include <iostream>
#include <set>
#include <vector>

//Функция нахождения минимального остовного дерева алгоритмом Прима
size_t GetMST(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph);
