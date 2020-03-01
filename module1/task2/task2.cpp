#include <iostream>
#include <stack>
#include <vector>

enum TVerticesColorType {
    VCT_WHITE,
    VCT_GREY,
    VCT_BLACK	
};

//Покраска всего графа и восстановление пути для топологической сортировки путём обхода в глубину
bool dfs(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& verticesColors, std::stack<int>& answerPath) {
	if(verticesColors[start] == VCT_GREY) {
        return false;
    }
    if(verticesColors[start] == VCT_WHITE) {
        verticesColors[start] = VCT_GREY;
    }
    if(verticesColors[start] == VCT_BLACK) {
        return true;
    }

    bool returnSuccess = true;

    for(size_t i = 0; i < graph[start].size(); ++i) {
        returnSuccess &= dfs(graph, graph[start][i], verticesColors, answerPath);
    }
    answerPath.push(start);
    verticesColors[start] = VCT_BLACK;
    return returnSuccess;
}

//Функция топологической сортировки. Используется алгоритм трех цветов
//Запускаем dfs от каждой неиспользованной вершины. Стоит заметить, что возможно уже при
//первом использовании dfs некоторые вершины будут покрашены, таким образом мы симулируем
//отдачу изначального приказа только тем полицейским, которые не могут ни от кого получить информацию
bool topological_sort(const std::vector<std::vector<int>>& graph, std::stack<int>& answer) {
    std::vector<int> color(graph.size());
    bool successSort = true;

    for(size_t i = 0; i < graph.size(); i++) {
        if(color[i] == VCT_WHITE) {
            successSort &= dfs(graph, i, color, answer);
        }
    }
    return successSort;
}

int main() {
    int vertexAmount = 0;
    int edgeAmount = 0;
    std::cin >> vertexAmount >> edgeAmount;
    std::vector<std::vector<int>> graph(vertexAmount);

    for(int i = 0; i < edgeAmount; ++i) {
        int from = 0
	int to = 0;
        std::cin >> from >> to;
        if(from == to) {
            //Петля - сразу NO
            std::cout << "NO";
            return 0;
        }
        graph[from].push_back(to);
    }

    bool succesSort = true;
    std::stack<int> answerPath;
    
    if(!topological_sort(graph, answerPath)) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES" << std::endl;
    while(!answerPath.empty()) {
        std::cout << answerPath.top() << ' ';
        answerPath.pop();
    }
    return 0;

}
