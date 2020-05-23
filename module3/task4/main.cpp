#include "task4.h"

int main() {

    size_t sizeX = 0;
    size_t sizeY = 0;
    long long costA = 0;
    long long costB = 0;
    std::cin >> sizeX >> sizeY >> costA >> costB;

    std::vector<std::string> bridge;
    for(size_t i = 0; i < sizeX; ++i) {
        std::string line;
        std::cin >> line;
        bridge.push_back(line);
    }

    std::cout << FixBridge(bridge, costA, costB) << std::endl;

    return 0;
}