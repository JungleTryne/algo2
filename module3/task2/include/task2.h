#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

//Функция получения MST алгоритмом Крускала
size_t GetMST(size_t graphSize, const std::vector<std::pair<size_t, std::pair<size_t, size_t>>>& constGraph);
