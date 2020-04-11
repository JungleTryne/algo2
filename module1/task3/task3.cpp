#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>


//Функция обхода в глубину. В out записывет времены выхода из вершины
void DFStoGetOutTimings(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& outTimings, std::vector<bool>& visited) {
    static int counter = 0;

    visited[start] = true;
    for(size_t i = 0; i < graph[start].size(); ++i) {
        if(!visited[graph[start][i]]) {
            DFStoGetOutTimings(graph, graph[start][i], outTimings, visited);
        }
    }

    outTimings[start] = counter;
    ++counter;
}


//Фукнция обхода в глубину. В buffer записывет вершины, которые мы посетили
void DFStoGetSCC(const std::vector<std::vector<int>>& graph, int start, std::vector<bool>& visited, std::vector<int>& buffer) {
    visited[start] = true;
    buffer.push_back(start);
    for(size_t i = 0; i < graph[start].size(); i++) {
        if(!visited[graph[start][i]]) {
            DFStoGetSCC(graph, graph[start][i], visited, buffer);
        }
    }
}


//Получить времена выхода из вершины при обходе в глубину
std::vector<int> getOutTimings(const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(graph.size());
    std::vector<int> outTimings(graph.size());
    for(size_t i = 0; i < graph.size(); ++i) {
        if(!visited[i]) {
            DFStoGetOutTimings(graph, i, outTimings, visited);
        }
    }
    return outTimings;
}


//Получить граф с перевернутыми рёбрами
std::vector<std::vector<int>> getReversedGraph(const std::vector<std::vector<int>>& initialGraph) {
    std::vector<std::vector<int>> reversedGraph(initialGraph.size());
    for(size_t i = 0; i < initialGraph.size(); ++i) {
        for(size_t j = 0; j < initialGraph[i].size(); ++j) {
            reversedGraph[initialGraph[i][j]].push_back(i);
        }
    }
    return reversedGraph;
}


//Возвращает вектор, где SCCvector[i] - уникальный номер компоненты звязности,
//которой принадлежит вершина i
std::vector<int> getSCCvector(const std::vector<std::vector<int>>& graph) {
    std::vector<int> outTimings = getOutTimings(graph);
    std::vector<std::vector<int>> reversedGraph = getReversedGraph(graph);
    std::vector<int> SCCarray(graph.size());

    for(size_t i = 0; i < SCCarray.size(); ++i) {
        SCCarray[i] = -1;
    }

    //outVertexes[i] - из какой вершины мы выходим на i-м шаге ("секунде")
    std::vector<int> outVertexes(graph.size());
    for(size_t i = 0; i < outTimings.size(); ++i) {
        outVertexes[outTimings[i]] = i;
    }

    int SCCNum = 0;
    std::vector<bool> visited(graph.size());
    for(int i = outVertexes.size()-1; i > -1 ; --i) {
        if(!visited[outVertexes[i]]) {
            std::vector<int> buffer;

            DFStoGetSCC(reversedGraph, outVertexes[i], visited, buffer);
            //Элементы buffer являются элементами одной компоненты связности
            for(size_t j = 0; j < buffer.size(); ++j) {
                SCCarray[buffer[j]] = SCCNum;
            }
            ++SCCNum;
        }
    }
    return SCCarray;
}


//Из изначального графа возвращает граф, где все компоненты связности заменены на вершины
std::vector<std::vector<int>> getSCCgraph(const std::vector<std::vector<int>>& initial, const std::vector<int>& SCCvector) {
    std::vector<std::vector<int>> SCCgraph(*std::max_element(SCCvector.begin(), SCCvector.end()) + 1);
    for(size_t i = 0; i < initial.size(); ++i) {
        for(size_t j = 0; j < initial[i].size(); ++j) {
            if(SCCvector[i] != SCCvector[initial[i][j]]) {
                //Нашли вершины, которые соединены ребром, но находятся в разных
                //компонентах связности -> компоненты связности соединяем этим ребром
                //в новом графе
                SCCgraph[SCCvector[i]].push_back(SCCvector[initial[i][j]]);
            }
        }
    }
    return SCCgraph;
}

//Возвращает количество вершин, которые не имеют детей
int getSinkAmount(const std::vector<std::vector<int>>& SCCgraph) {
    int sinkAmount = 0;
    for(size_t i = 0; i < SCCgraph.size(); ++i) {
        if(SCCgraph[i].size() == 0) {
            ++sinkAmount;
        }
    }
    return sinkAmount;
}

//Возвращает количество вершин, которые не имеют родителей
int getSourceAmount(const std::vector<std::vector<int>>& SCCgraph) {
    int sourceAmount = 0;
    std::vector<std::vector<int>> reversedSCCgraph = getReversedGraph(SCCgraph);
    for(size_t i = 0; i < reversedSCCgraph.size(); ++i) {
        if(reversedSCCgraph[i].size() == 0) {
            ++sourceAmount;
        }
    }
    return sourceAmount;
}

int getNumOfAdditionalEdges(const std::vector<std::vector<int>>& graph) {
    std::vector<int> SCCvector = getSCCvector(graph);
    std::vector<std::vector<int>> SCCgraph = getSCCgraph(graph, SCCvector);

    //Если только одна компонента связности, то все ок, ничего добавлять не надо
    if(SCCgraph.size() == 1) {
        return 0; 
    }

    int sinkAmount = getSinkAmount(SCCgraph);
    int sourceAmount = getSourceAmount(SCCgraph);

    return std::max(sinkAmount, sourceAmount);
}

int main() {
    int vertextAmount = 0;
    int edgeAmount = 0;
    std::cin >> vertextAmount >> edgeAmount;

    std::vector<std::vector<int>> graph(vertextAmount);

    for(int i = 0; i < edgeAmount; ++i) {
        int from = 0;
        int to = 0;
        std::cin >> from >> to;
        graph[from-1].push_back(to-1);
    }

    std::cout << getNumOfAdditionalEdges(graph) << std::endl;

    return 0;
}