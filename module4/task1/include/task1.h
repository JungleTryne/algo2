#pragma once

#include <iostream>
#include <vector>

class SecondStatistics {
private:
    std::vector<size_t> logarithms;

    //Первый элемент пары - число, второй - индекс в изначальном массиве
    std::vector<std::vector<std::pair<int, size_t>>> sparseTable;
    std::pair<int, size_t> getMinOnRange(size_t left, size_t right);
    size_t getLogarithm(size_t len);
public:
    explicit SecondStatistics(const std::vector<int>& array);
    int getSecondStatistics(size_t left, size_t right);
};
