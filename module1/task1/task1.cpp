#include <iostream>
#include <vector>
#include <queue>


//Находим для каждой вершины графа кол-во шагов, которое нужно пройти, чтобы дойти от вершины
//from до этой вершины. Возвращаем вектор расстояний 
std::vector<int> find_distances(std::vector<std::vector<int>> graph, int from) {
    std::vector<int> distances(graph.size());
    std::vector<bool> visited(graph.size());
    std::queue<int> bfs;
    bfs.push(from);
    visited[from] = true;

    while(!bfs.empty()) {
        int current_node = bfs.front();
        bfs.pop();
        for(size_t i = 0; i < graph[current_node].size(); ++i) {
            int to = graph[current_node][i];
            if(!visited[to]) {
                visited[to] = true;
                distances[to] = distances[current_node] + 1;
                bfs.push(to);
            }
        }
    }

    return distances;
}

int main() {
    int vertexNum = 0;
    int edgeNum = 0;

    std::cin >> vertexNum;
    std::cin >> edgeNum;

    int leonVertex = 0;
    int malVertex = 0;
    int milkVertex = 0;
    std::cin >> leonVertex >> malVertex >> milkVertex;

    leonVertex--; //Нумерация вершин с 1, а я хочу с нуля
    malVertex--;
    milkVertex--;

    std::vector<std::vector<int>> graph(vertexNum);
    for(size_t i = 0; i < edgeNum; ++i) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        graph[a-1].push_back(b-1);
        graph[b-1].push_back(a-1);
    }
    
    std::vector<int> milk_distances = find_distances(graph, milkVertex);
    std::vector<int> leo_distances = find_distances(graph, leonVertex);
    std::vector<int> mal_distances = find_distances(graph, malVertex);

    int min_answer = milk_distances[0] + leo_distances[0] + mal_distances[0];
    for(int i = 1; i < vertexNum; i++) {
        int new_answer = milk_distances[i] + leo_distances[i] + mal_distances[i];
        min_answer = (min_answer < new_answer ? min_answer : new_answer);
    }

    std::cout << min_answer;
    

    return 0;
}
