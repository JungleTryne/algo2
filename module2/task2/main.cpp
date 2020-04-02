#include <iostream>
#include <vector>

#include "task2.h"

using std::cin;
using std::cout;

int main() {
    int vertexCount = 0, edgeCount = 0, limit = 0, rickFrom = 0, rickTo = 0;
    cin >> vertexCount >> edgeCount >> limit >> rickFrom >> rickTo;

    vector<vector<pair<size_t,int>>> graph(vertexCount);
    for (int i = 0; i < edgeCount; ++i) {
        int from = 0, to = 0, cost = 0;
        cin >> from >> to >> cost;
        graph[from-1].push_back(std::make_pair(to-1, cost));
    }

    cout << solveProblem(graph, limit, rickFrom, rickTo);
    return 0;
}
