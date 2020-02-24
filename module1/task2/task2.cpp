#include <iostream>
#include <vector>
#include <stack>

void dfs(const std::vector<std::vector<int>> &graph, int start, std::vector<int> &color, std::stack<int> &answer, bool &flag) {
    /* Функция поиска в глубину
    :param graph: граф
	:param start: откуда стартуем dfs
	:param color: используем алгоритм топ. сортировки методом 3х цветов
    	Этот массив как раз хранит цвета вершин
    :param flag: При запуске dfs он true. Если найден цикл, то false
    :param answer: Храним пройденный путь
    */
	if(color[start] == 1) {
        flag = false;
        return;
    }
    if(color[start] == 0) {
        color[start] = 1;
    }
    if(color[start] == 2) return;

    for(int i = 0; i < graph[start].size(); ++i) {
        dfs(graph, graph[start][i], color, answer, flag);
    }
    answer.push(start);
    color[start] = 2;
}

std::stack<int> topological_sort(std::vector<std::vector<int>> graph, bool& ok) {
	/* Функция топологической сортировки. Используется алгоритм трех цветов
    Запускаем dfs от каждой неиспользованной вершины. Стоит заметить, что возможно уже при
    первом использовании dfs некоторые вершины будут покрашены, таким образом мы симулируем
    отдачу изначального приказа только тем полицейским, которые не могут ни от кого получить информацию
    
    */
    std::vector<int> color(graph.size());
    bool flag = true;
    std::stack<int> answer;
    for(int i = 0; i < graph.size(); i++) {
        if(color[i] == 0) dfs(graph, i, color, answer, flag);
    }

    if(flag) {
        ok = true;
        return answer;
    } else {
        ok = false;
        return {};
    }
    
}

int main() {
    int v = 0;
    int e = 0;
    std::cin >> v >> e;
    std::vector<std::vector<int>> graph(v);
    for(int i = 0; i < e; ++i) {
        int a = 0, b = 0;
        std::cin >> a >> b;
        if(a == b) {
            std::cout << "NO";
            return 0;
        }
        graph[a].push_back(b);
    }
    bool ok = true;
    std::stack<int> answer = topological_sort(graph, ok);
    if(!ok) {
        std::cout << "NO";
        return 0;
    }
    std::cout << "YES" << std::endl;
    while(!answer.empty()) {
        std::cout << answer.top() << ' ';
        answer.pop();
    }
    return 0;

}
