#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

//Структура, которая позволяет хэшировать пары для использования их в unordered_map
struct pair_hash {
    template <typename T1, typename T2>
    std::size_t operator () (const std::pair<T1,T2> &pair) const;
};

//Алгоритм Куна для нахождения максимального паросочетания
bool KuhnAlgorithm(size_t from, const std::vector<std::vector<size_t>>& graph, std::vector<long long>& pairs,
        std::vector<bool>& visited);

//Функция для преобразования моста в граф
void GetBipartiteGraph(const std::vector<std::string>& bridge, std::vector<std::pair<size_t, size_t>>& firstHalf,
                       std::vector<std::pair<size_t, size_t>>& secondHalf, std::vector<std::vector<size_t>>& graph);

//Функция нахождения стоимости починки моста
long long FixBridge(const std::vector<std::string>& bridge, long long priceA, long long priceB);