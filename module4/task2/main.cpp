#include "task2.h"

int main() {
    size_t stationsCount = 0;
    std::cin >> stationsCount;

    std::vector<size_t> initialData;
    for (size_t i = 0; i < stationsCount - 1; ++i) {
        size_t temp = 0;
        std::cin >> temp;
        initialData.push_back(temp);
    }

    size_t trainCapacity = 0;
    std::cin >> trainCapacity;

    SegmentTree tree(initialData, trainCapacity);

    size_t queryCount = 0;
    std::cin >> queryCount;

    size_t tempLeft = 0;
    size_t tempRight = 0;
    size_t ticketAmount = 0;
    for (size_t i = 0; i < queryCount; ++i) {
        std::cin >> tempLeft >> tempRight >> ticketAmount;
        if (tree.getMax(tempLeft, tempRight - 1) + ticketAmount > trainCapacity) {
            std::cout << i << ' ';
        } else {
            tree.updateTree(tempLeft, tempRight-1, ticketAmount);
        }
    }
    return 0;
}