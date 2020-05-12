#include "task3.h"

int main() {
    size_t graphSize = 0;
    size_t specialOffersSize = 0;
    std::cin >> graphSize >> specialOffersSize;

    std::vector<size_t> prices;
    for (size_t i = 0; i < graphSize; ++i) {
        size_t temp;
        std::cin >> temp;
        prices.push_back(temp);
    }

    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> specialOffers;
    size_t from = 0;
    size_t to = 0;
    size_t price = 0;
    for (size_t i = 0; i < specialOffersSize; ++i) {
        std::cin >> from >> to >> price;
        specialOffers.emplace_back(price, std::make_pair(to - 1, from - 1));
    }

    std::vector<std::vector<std::pair<size_t, size_t>>> graph;
    GetBestGraph(prices, specialOffers, graph);
    std::cout << GetMST(graph) << std::endl;

    return 0;
}