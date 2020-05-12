#pragma once

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <fstream>

//Функция нахождения MST алгоритмом Прима
size_t GetMST(const std::vector<std::vector<std::pair<size_t, size_t>>>& graph);

//Функция нахождения самого дешевого связного графа
void GetBestGraph(const std::vector<size_t>& prices,
                  const std::vector<std::pair<size_t, std::pair<size_t, size_t>>>& specialOffers,
                  std::vector<std::vector<std::pair<size_t, size_t>>>& output);