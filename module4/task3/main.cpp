#include "task3.h"

int main() {
    size_t stationsCount = 0;
    std::cin >> stationsCount;

    std::vector<size_t> initialData;
    for (size_t i = 0; i < stationsCount; ++i) {
        size_t red = 0;
        size_t green = 0;
        size_t blue = 0;
        std::cin >> red >> green >> blue;
        initialData.push_back(red + green + blue);
    }

    SegmentTree tree(initialData);

    size_t queryCount = 0;
    std::cin >> queryCount;

    size_t tempLeft = 0;
    size_t tempRight = 0;
    size_t red = 0;
    size_t green = 0;
    size_t blue = 0;
    size_t photoLeft = 0;
    size_t photoRight = 0;
    for (size_t i = 0; i < queryCount; ++i) {
        std::cin >> tempLeft >> tempRight >> red >> green >> blue >> photoLeft >> photoRight;
        tree.updateTree(tempLeft, tempRight, red + green + blue);
        std::cout << tree.getMin(photoLeft, photoRight) << ' ';
    }
    return 0;
}