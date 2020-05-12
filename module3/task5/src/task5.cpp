#include "task5.h"

//Алгоритм нахождения увеличивающего пути в графе
bool GetAdditivePath(std::vector<bool>& visited,
                     std::vector<int>& prefixFlow,
                     std::vector<size_t>& parent,
                     std::vector<size_t>& distance,
                     const std::vector<std::vector<std::pair<int, int>>>& capacity,
                     const std::vector<std::vector<std::pair<int, int>>>& currentFlow,
                     size_t graphSize, size_t from, size_t to)
{
    visited = std::vector<bool> (graphSize, false);
    prefixFlow = std::vector<int> (graphSize, 0);
    parent = std::vector<size_t>(graphSize, 0);
    distance = std::vector<size_t>(graphSize, 0);

    visited[from] = true;
    parent[from] = from;
    prefixFlow[from] = 1e5;

    std::queue<size_t> bfs;
    bfs.push(from);
    while(!bfs.empty() && !visited[to]) {
        size_t currentVertex = bfs.front();
        bfs.pop();

        for(size_t i = 0; i < capacity[currentVertex].size(); ++i) {
            size_t toVertex = capacity[currentVertex][i].first;
            assert(static_cast<size_t>(currentFlow[currentVertex][i].first) == toVertex);
            int toFlow = currentFlow[currentVertex][i].second;
            int toCapacity = capacity[currentVertex][i].second;

            if(!visited[toVertex] && (toCapacity - toFlow > 0)) {
                prefixFlow[toVertex] = prefixFlow[currentVertex];
                if(toCapacity - toFlow < prefixFlow[toVertex]) {
                    prefixFlow[toVertex] = toCapacity - toFlow;
                }

                visited[toVertex] = true;
                parent[toVertex] = currentVertex;
                bfs.push(toVertex);
            }
        }
    }
    return visited[to];
}

//Функция нахождения путей для героев
void GetPaths(std::vector<std::vector<std::pair<int, int>>> currentFlow, size_t from, size_t to,
              std::vector<size_t>& firstPath, std::vector<size_t>& secondPath)
{
    std::vector<size_t> history;
    std::stack<size_t> dfs;

    for(int k = 0; k < 2; ++k) {
        dfs.push(from);

        while(!dfs.empty()) {
            size_t currentVertex = dfs.top();
            history.push_back(currentVertex);
            if(currentVertex == to) {
                break;
            }
            dfs.pop();
            for(auto& edge : currentFlow[currentVertex]) {
                short ourFlow = edge.second;
                if(ourFlow > 0) {
                    dfs.push(edge.first);
                    edge.second--;
                    break;
                }
            }
        }

        if (k == 0) {
            firstPath = history;
        } else {
            secondPath = history;
        }
        history.clear();
        while(!dfs.empty()) {
            dfs.pop();
        }
    }
}

//Алгоритм нахождения максимального потока в графе
//В firstPath и secondPath записываются соответствующие пути, по которым должны пойти герои задачи
size_t GetMaxFlow(const std::vector<std::vector<std::pair<int, int>>>& capacity,
                  std::vector<std::vector<std::pair<int, int>>>& currentFlow, size_t graphSize, size_t from, size_t to,
                  std::vector<size_t>& firstPath, std::vector<size_t>& secondPath)
{
    std::vector<bool> visited(graphSize, false);
    std::vector<int> prefixFlow(graphSize, 0);
    std::vector<size_t> parent(graphSize, 0);
    std::vector<size_t> distance(graphSize, 0);
    size_t flow = 0;

    while (GetAdditivePath(visited, prefixFlow, parent, distance, capacity, currentFlow, graphSize, from, to)) {
        size_t vertexOne = to;
        size_t vertexTwo = parent[to];
        while(vertexOne != from) {
            //Обновляем текущее состояние после нахождения увеличивающего пути
            for(auto& edge : currentFlow[vertexTwo]) {
                if(static_cast<size_t>(edge.first) == vertexOne) {
                    edge.second += 1;
                    break;
                }
            }

            for(auto& edge : currentFlow[vertexOne]) {
                if(static_cast<size_t>(edge.first) == vertexTwo) {
                    edge.second -= 1;
                    break;
                }
            }

            //Идем к предкам, тем самым обходя увеличивающий путь
            vertexOne = vertexTwo;
            vertexTwo = parent[vertexOne];
        }
        flow += 1;
    }

    GetPaths(currentFlow, flow, to, firstPath, secondPath);
    return flow;
}
