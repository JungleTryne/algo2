#include "task1.h"

int main() {
    size_t arraySize = 0;
    size_t numberOfRanges = 0;
    std::cin >> arraySize >> numberOfRanges;

    std::vector<int> array;
    for (size_t i = 0; i < arraySize; ++i) {
        int temp = 0;
        std::cin >> temp;
        array.push_back(temp);
    }

    SecondStatistics s(array);

    for (size_t i = 0; i < numberOfRanges; ++i) {
        size_t left = 0;
        size_t right = 0;
        std::cin >> left >> right;
        std::cout << s.getSecondStatistics(left-1, right-1) << std::endl;
    }

    return 0;
}