#include "task1.h"

//Фукнция получения целочисленного логарифма
//Используется для реализации SparseTable
size_t SecondStatistics::getLogarithm(size_t len) {
    if (len == 1) {
        return 0;
    }
    return getLogarithm(len / 2) + 1;
}

//Конструктор sparseTable
SecondStatistics::SecondStatistics(const std::vector<int> &array) {
    for (size_t i = 1; i < array.size() + 1; ++i) {
        this->logarithms.push_back(getLogarithm(i));
    }

    sparseTable = std::vector<std::vector<std::pair<int, size_t>>>(array.size(),
            std::vector<std::pair<int, size_t>>(this->getLogarithm(array.size()) + 1, 
                    std::make_pair(-1,0)));

    for (size_t i = 0; i < array.size(); ++i) {
        sparseTable[i][0] = std::make_pair(array[i], i);
    }

    for (size_t i = 1; (1u << i) <= array.size(); ++i) {
        for (size_t j = 0; (j + (1u << i) - 1) < array.size(); ++j) {
            if (sparseTable[j][i - 1].first < sparseTable[j + (1u << (i - 1))][i - 1].first) {
                sparseTable[j][i] = sparseTable[j][i - 1];
            } else {
                sparseTable[j][i] = sparseTable[j + (1u << (i - 1))][i - 1];
            }
        }
    }
}

std::pair<int, size_t> SecondStatistics::getMinOnRange(size_t left, size_t right) {
    size_t a = logarithms[right - left];

    if (sparseTable[left][a] <= sparseTable[right - (1u << a) + 1][a]) {
        return sparseTable[left][a];
    }
    return sparseTable[right - (1u << a) + 1][a];
}

int SecondStatistics::getSecondStatistics(size_t left, size_t right) {
    std::pair<int, size_t> minimum = this->getMinOnRange(left, right);

    //Минимумом разделяем массив на 2 части
    std::pair<int, size_t> secondMinimumFirst = {1e9,0};
    if (minimum.second != left) {
        secondMinimumFirst = this->getMinOnRange(left, minimum.second - 1);
    }

    std::pair<int, size_t> secondMinimumSecond = {1e9,0};
    if (minimum.second != right) {
        secondMinimumSecond = this->getMinOnRange(minimum.second + 1, right);
    }

    return secondMinimumFirst.first < secondMinimumSecond.first ? secondMinimumFirst.first : secondMinimumSecond.first;
}
