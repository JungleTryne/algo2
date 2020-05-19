#include "task4.h"

int main() {
    size_t graphSize = 0;
    size_t queryCount = 0;

    std::cin >> graphSize >> queryCount;
    std::vector<size_t> parents(graphSize);
    for (size_t i = 1; i < graphSize; ++i) {
        size_t temp;
        std::cin >> temp;
        parents[i] = temp;
    }

    LCA lca(parents);

    long long x = 0;
    long long y = 0;
    long long z = 0;
    long long aOne = 0;
    long long aTwo = 0;
    long long tempAOne = 0;
    long long tempATwo = 0;
    std::cin >> aOne >> aTwo >> x >> y >> z;

    size_t answer = lca.getLCA(aOne, aTwo);
    long long sum = answer;
    long long lastAnswer = answer;

    for (long long i = 3; i < 2 * queryCount; i += 2) {
        tempAOne = (x * aOne + y * aTwo + z) % static_cast<long long>(parents.size());
        tempATwo = (x * aTwo + y * tempAOne + z) % static_cast<long long>(parents.size());
        answer = lca.getLCA((tempAOne + lastAnswer) % parents.size(), tempATwo);
        aOne = tempAOne;
        aTwo = tempATwo;
        lastAnswer = answer;
        sum += static_cast<long long>(answer);
    }

    std::cout << sum;

    return 0;
}