#include "task5.h"

int main() {
    size_t vertexCount = 0;
    size_t edgeCount;
    size_t from = 0;
    size_t to = 0;
    std::cin >> vertexCount >> edgeCount >> from >> to;

    std::vector<std::vector<std::pair<int, int>>> capacity(vertexCount, std::vector<std::pair<int,int>>(0));
    std::vector<std::vector<std::pair<int, int>>> currentFlow(vertexCount, std::vector<std::pair<int,int>>(0));

    for(size_t i = 0; i < edgeCount; ++i) {
        size_t first;
        size_t second;
        std::cin >> first >> second;

        if(first != second) {
            bool found = false;
            for(auto& i : capacity[first-1]) {
                if(i.first == second-1) {
                    i.second += 1;
                    found = true;
                    break;
                }
            }
            if(!found) {
                capacity[first-1].push_back(std::make_pair(second-1, 1));
                currentFlow[first-1].push_back(std::make_pair(second-1, 0));
            }

            found = false;
            for(auto& edgeCapacity : capacity[second - 1]) {
                if(edgeCapacity.first == first - 1) {
                    found = true;
                    break;
                }
            }
            if(!found) {
                capacity[second-1].push_back(std::make_pair(first-1, 0));
                currentFlow[second-1].push_back(std::make_pair(first-1, 0));
            }

        }
    }

    if(!edgeCount) {
        if(from == to) {
            std::cout << "YES\n" << from << '\n' << from << std::endl;
        } else {
            std::cout << "NO\n";
        }
        return 0;
    }

    std::vector<size_t> firstPath;
    std::vector<size_t> secondPath;

    size_t flow = GetMaxFlow(capacity, currentFlow, vertexCount, from-1, to-1, firstPath, secondPath);
    if(flow < 2) {
        std::cout << "NO" << std::endl;
        return 0;
    }
    std::cout << "YES" << std::endl;
    for(auto i : firstPath) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    for(auto i : secondPath) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    return 0;
}