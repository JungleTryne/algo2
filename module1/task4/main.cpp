//Данила Мишин, Б05-927
//4 задача, Гамма алгоритм

#include <algorithm>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

//Функция для удаления ребер GPlane из графа
std::vector<std::vector<int>> GetGraphWithoutGplane(const std::vector<std::vector<int>>& faces, 
    const std::vector<std::vector<int>>& graph) 
{
    std::vector<std::vector<int>> graphWithoutGplane = graph;

    for( size_t i = 0; i < faces.size(); ++i ) {
        std::vector<int> currentFace = faces[i];
        currentFace.push_back(currentFace[0]);
        for( size_t j = 0; j < currentFace.size()-1; ++j ) {
            graphWithoutGplane[currentFace[j]].erase(
                    remove(graphWithoutGplane[currentFace[j]].begin(), 
                    graphWithoutGplane[currentFace[j]].end(), 
                    currentFace[j+1]
                ), 
                graphWithoutGplane[currentFace[j]].end()
            );

            graphWithoutGplane[currentFace[j+1]].erase(
                remove(graphWithoutGplane[currentFace[j+1]].begin(), 
                graphWithoutGplane[currentFace[j+1]].end(), 
                currentFace[j]
                ), 
                graphWithoutGplane[currentFace[j+1]].end()
            );
        }
    }

    return graphWithoutGplane;
}

enum TVerticesColorType {
    VCT_WHITE,
    VCT_GRAY,
    VCT_BLACK
};

//DFS для нахождения цикла в графе. Использует алгоритм 3х цветов
void DFSForCycleFinding(const std::vector<std::vector<int>>& graph, int from, std::vector<int>& color, 
    std::vector<int>& history, bool& success, int parent = -1) 
{
    if( success ) {
        return;
    }
    color[from] = VCT_GRAY;
    history.push_back(from);

    for( size_t i = 0; i < graph[from].size(); ++i ) {
        if( success ) {
            return;
        }
        if( color[graph[from][i]] == VCT_WHITE ) {
            DFSForCycleFinding(graph, graph[from][i], color, history, success, from);
        }
        else if( color[graph[from][i]] == VCT_GRAY && parent != graph[from][i] ) {
            history.push_back(graph[from][i]);
            success = true;
            return;
        }
    }
    color[from] = VCT_BLACK;
}

//Нахождение простого цикла в графу. Возвращает true, если цикл найден, цикл записывается в vector cycle
bool FindCycle(const std::vector<std::vector<int>>& graph, std::vector<int>& cycle ) {
    std::vector<int> history;
    std::vector<int> color(graph.size());

    bool successFind = false;
    for( size_t i = 0; i < graph.size(); ++i ) {
        if( color[i] == 0 ) {
            bool success = false;
            DFSForCycleFinding(graph, i, color, history, success);
            if( success ) {
                successFind = success;
                break;
            }
        }
    }
    int cycleRingVertex = history[history.size()-1];
    cycle.push_back(cycleRingVertex);
    for( int i = history.size()-2; i > -1; --i ) {
        if( history[i] == cycleRingVertex ) {
            break;
        }
        cycle.push_back(history[i]);
    }
    return successFind;
}

//Структура сегмента для работы алгоритм
struct Segment {
    std::set<int> allVertex;
    std::set<int> contactVertex;
};

//Проверяет, является ли вершина контактной
bool IsContact(const std::set<int>& faces_set, int vertex) {
    return faces_set.find(vertex) != faces_set.end();
}

//DFS для нахождения компонент второго типа
void DFSForComponent(int from, const std::vector<std::vector<int>>& graph, const std::set<int>& faces_set, 
    std::set<int>& history, std::set<int>& contact, std::vector<bool>& visited, int parent = -1) 
{
    history.insert(from);
    visited[from] = true;

    if( IsContact(faces_set, from) ) {
        contact.insert(from);
        if( parent != -1 ) {
            return;
        }

    }

    for( size_t i = 0; i < graph[from].size(); ++i) {
        if( graph[from][i] != parent && !visited[graph[from][i]] ) {
            DFSForComponent(graph[from][i], graph, faces_set, history, contact, visited, from);
        }
    }
}

//DFS для нахождения цепи в сегменте
void DFSForChain(int from, int initialVertex, bool& chainFound, const std::vector<std::vector<int>>& graph, 
    std::vector<bool> visited, const Segment& segment, std::vector<int> history, std::vector<int>& chain) 
{
    visited[from] = true;
    history.push_back(from);

    if( segment.contactVertex.find(from) != segment.contactVertex.end() && from != initialVertex ) {
        chain = history;
        chainFound = true;
        return;
    }

    for( size_t i = 0; i < graph[from].size(); ++i) {
        int to = graph[from][i];
        if( !visited[to] && segment.allVertex.find(to) != segment.allVertex.end() && 
            !chainFound && to != initialVertex ) 
        {
            DFSForChain(to, initialVertex, chainFound, graph, visited, segment, history, chain);
        }
    }
}

//Удаление цепи из графа (Используется для графа: исходный граф \ gplane)
void RemoveChainFromGraph(std::vector<std::vector<int>>& graph, std::vector<int> chain) {
    for( size_t i = 0; i < chain.size()-1; ++i ) {
        graph[chain[i]].erase(remove(graph[chain[i]].begin(), graph[chain[i]].end(), chain[i+1]), 
            graph[chain[i]].end()
        );
        graph[chain[i+1]].erase(remove(graph[chain[i+1]].begin(), graph[chain[i+1]].end(), chain[i]), 
            graph[chain[i+1]].end()
        );
    }
}

//Удаляем сегменты дубликаты
void RemoveEqualSegments(std::vector<Segment>& segments) {
    std::vector<Segment> newSegments;
    for( size_t i = 0; i < segments.size(); ++i ) {
        bool notInNewSegments = true;
        for( size_t j = 0; j < newSegments.size(); ++j ) {
            if( newSegments[j].contactVertex == segments[i].contactVertex && 
                newSegments[j].allVertex == segments[i].allVertex ) 
            {
                notInNewSegments = false;
                break;
            }
        }
        if( notInNewSegments ) {
            newSegments.push_back(segments[i]);
        }
    }
    segments = newSegments;
}

//Получение сегментов первого типа
void GetFirstTypeSegments(std::vector<std::vector<int>>& graphWithoutGplane,
                    std::vector<Segment>& segments,
                    const std::set<int>& facesSet) 
{
    for( size_t i = 0; i < graphWithoutGplane.size(); ++i ) {
        for( size_t j = i+1; j < graphWithoutGplane.size(); ++j ) {
            auto position = std::find(graphWithoutGplane[i].begin(), graphWithoutGplane[i].end(), j);
            if( position != graphWithoutGplane[i].end() && facesSet.find(i) != facesSet.end() && 
                facesSet.find(j) != facesSet.end() ) 
            {
                Segment segment;
                segment.contactVertex.insert(i);
                segment.contactVertex.insert(j);
                segment.allVertex.insert(i);
                segment.allVertex.insert(j);
                segments.push_back(segment);
            }
        }
    }
}

//Удаление сегментов первого типа из graphWithoutGplane для облегчения поиска сегментов второго типа
void RemoveFirstTypeSegmentsFromGraph(std::vector<Segment>& segments, std::vector<std::vector<int>> graphWithoutGplane) {
    for( size_t i = 0; i < segments.size(); ++i ) {
        std::vector<int> segment_vector;
        segment_vector.assign(segments[i].allVertex.begin(), segments[i].allVertex.end());

        int one = segment_vector[0];
        int two = segment_vector[1];

        auto position = std::find(graphWithoutGplane[one].begin(), graphWithoutGplane[one].end(), two);
        if ( position != graphWithoutGplane[one].end() )
            graphWithoutGplane[one].erase(position);
        position = std::find(graphWithoutGplane[two].begin(), graphWithoutGplane[two].end(), one);
        if ( position != graphWithoutGplane[two].end() )
            graphWithoutGplane[two].erase(position);
    }
}

//Функция получения сегментов второго типа
void GetSecondTypeSegments(std::vector<std::vector<int>> graphWithoutGplane, std::vector<Segment> segments, std::set<int> facesSet) {
    std::vector<bool> visited(graphWithoutGplane.size());
    for( size_t i = 0; i < graphWithoutGplane.size(); ++i ) {
        RemoveEqualSegments(segments);

        if( !graphWithoutGplane[i].empty() && !visited[i] ) {
            bool iscontact = facesSet.find(i) != facesSet.end();
            if( iscontact ) {
                for( size_t j = 0; j < graphWithoutGplane[i].size(); ++j ) {
                    std::vector<bool> visited(graphWithoutGplane.size());
                    std::set<int> history;
                    std::set<int> contact;
                    DFSForComponent(graphWithoutGplane[i][j], graphWithoutGplane, facesSet, history, contact, visited);
                    Segment s;
                    s.allVertex = history;
                    s.contactVertex = contact;
                    segments.push_back(s);
                }
            }
        }
    }
}

//Функция получение сегментов
void GetSegments(const std::vector<std::vector<int>>& faces,
                    std::vector<std::vector<int>>& graphWithoutGplane,
                    std::vector<Segment>& segments) 
{
    
    segments = {};

    std::set<int> facesSet;
    for( size_t i = 0; i < faces.size(); ++i ) {
        for( size_t j = 0; j < faces[i].size(); ++j ) {
            facesSet.insert(faces[i][j]);
        }
    }

    GetFirstTypeSegments(graphWithoutGplane, segments, facesSet);
    
    std::vector<std::vector<int>> graphWithoutCycle = graphWithoutGplane;

    RemoveFirstTypeSegmentsFromGraph(segments, graphWithoutGplane);

    GetSecondTypeSegments(graphWithoutGplane, segments, facesSet);
    
}

//Первый шаг алгоритма. Возвращает true, если цикл не найден
bool InitialPreparations(const std::vector<std::vector<int>>& graph, 
                            std::vector<std::vector<int>>& faces,
                            std::vector<Segment>& segments,
                            std::vector<std::vector<int>>& graphWithoutGPlane) {

    std::vector<int> cycle;
    if( !FindCycle(graph, cycle) ) {
        return true;
    }

    faces.push_back(cycle);
    faces.push_back(cycle);

    std::vector<std::vector<int>> graphWithoutGplane = GetGraphWithoutGplane(faces, graph);
    
    GetSegments(faces, graphWithoutGplane, segments);
    
    RemoveEqualSegments(segments);
    return false;
}

//Разделим грань найденной цепью. Результат помещается в faceOne, faceTwo
void SplitFaceWithChain(const std::vector<std::vector<int>>& graphWithoutGplane, std::vector<int>& face, 
    const std::vector<int>& chain, std::vector<int>& faceOne, std::vector<int>& faceTwo) 
{
    int positionOfFirstElementOfChain = find(face.begin(), face.end(), chain[0]) - face.begin();
        int positionOfSecondElementOfChain = find(face.begin(), face.end(), chain[chain.size()-1]) - face.begin();

        for( int i = positionOfFirstElementOfChain; i != positionOfSecondElementOfChain; i = (i+1)%face.size() ) {
            faceOne.push_back(face[i]);
        }
        faceOne.push_back(face[positionOfSecondElementOfChain]);

        for( int i = positionOfSecondElementOfChain; i != positionOfFirstElementOfChain; i = (i+1)%face.size() ) {
            faceTwo.push_back(face[i]);
        }
        faceTwo.push_back(face[positionOfFirstElementOfChain]);


        std::vector<int> childrenOfFaceOne = graphWithoutGplane[faceOne[faceOne.size()-1]];
        std::vector<int> childrenOfFaceTwo = graphWithoutGplane[faceTwo[faceTwo.size()-1]];

        if( faceOne[faceOne.size()-1] == chain[0] ) {
            for( size_t i = 1; i < chain.size()-1; ++i ) {
                faceOne.push_back(chain[i]);
            }
        } else {
            for( size_t i = chain.size()-2; i > 0 ; --i ) {
                faceOne.push_back(chain[i]);
            }
        }

        if( faceTwo[faceTwo.size()-1] == chain[0] ){
            for( size_t i = 1; i < chain.size()-1; ++i ) {
                faceTwo.push_back(chain[i]);
            }
        } else {
            for( size_t i = chain.size()-2; i > 0 ; --i ) {
                faceTwo.push_back(chain[i]);
            }
        }

}

//Основой алгоритм. Запускает проверу планарности компоненты графа
bool IsComponentPlanar(const std::vector<std::vector<int>>& graph) {
    
    std::vector<std::vector<int>> faces;
    std::vector<Segment> segments;
    std::vector<std::vector<int>> graphWithoutGplane;
    bool noCycle = InitialPreparations(graph, faces, segments, graphWithoutGplane);

    if( noCycle ) {
        return true;
    }

    while( !segments.empty() ) {

        //Создаем set граней, чтобы было легче определять контактность вершины
        std::vector<std::set<int>> faces_set;
        for( const auto& face : faces ) {
            std::set<int> face_set;
            for( auto element : face ) {
                face_set.insert(element);
            }
            faces_set.push_back(face_set);
        }

        std::vector<int> availableFaces(segments.size()); //Количество граней, в которые можно вставить segments[i]
        std::vector<int> availableFaceId(segments.size()); //индекс грани, в которую можно вставить segments[i]

        //Проверяем, можно ли вставить сегмент в каждую грань
        for( size_t i = 0; i < segments.size(); ++i ) {
            for( size_t j = 0; j < faces_set.size(); ++j ) {
                bool breaked = false;
                for( auto vertex : segments[i].contactVertex ) {
                    if( faces_set[j].end() == faces_set[j].find(vertex) ) {
                        breaked = true;
                    }
                }
                if( !breaked ) {
                    availableFaces[i]++;
                    availableFaceId[i] = j;
                }
            }
        }

        int segmentWithMinimalG = 0;
        int minimalG = availableFaces[0];

        //Находим сегмент, который можно вставить в меньшее количество граней
        for( size_t i = 1; i < segments.size(); ++i ) {
            if( availableFaces[i] < minimalG ) {
                minimalG = availableFaces[i];
                segmentWithMinimalG = i;
            }
        }

        if( minimalG == 0 ) {
            return false; //Нельзя вставить какой-то сегмент - граф не планарен
        }

        //Выбираем сегмент и грань для вставки
        std::vector<int> faceToBeInserted = faces[availableFaceId[segmentWithMinimalG]];

        Segment currentSegment = segments[segmentWithMinimalG];

        graphWithoutGplane = GetGraphWithoutGplane(faces, graph);

        //Находим цепь
        bool chainFound = false;
        int currentVertex = *currentSegment.contactVertex.begin();
        std::vector<bool> visited(graph.size());
        std::vector<int> chain;
        std::vector<int> history;

        DFSForChain(currentVertex, currentVertex, chainFound, graphWithoutGplane, 
        visited, currentSegment, history, chain);
        
        if( !chainFound ) {
            return false;
        }

        //Делим грань цепью
        std::vector<int> faceOne;
        std::vector<int> faceTwo;

        SplitFaceWithChain(graphWithoutGplane, faceToBeInserted, chain, faceOne, faceTwo);

        faces.erase(faces.begin() + availableFaceId[segmentWithMinimalG]);
        faces.push_back(faceOne);
        faces.push_back(faceTwo);

        //Обновляем set граней
        faces_set = {};
        for( const auto& face : faces ) {
            std::set<int> face_set;
            for( auto element : face ) {
                face_set.insert(element);
            }
            faces_set.push_back(face_set);
        }

        //Удаляем цепь и GPlane, т.к. она стала частью граней
        RemoveChainFromGraph(graphWithoutGplane, chain);

        //Сегмент разделится на несколько сегментов или исчезнет?

        if( chain.size() == currentSegment.allVertex.size() ) {
            //Вся цепь - сегмент. Поэтому просто удаляем сегмент и продолжаем алгоритм
            segments.erase(segments.begin() + segmentWithMinimalG);
            continue;

        } else {
            //Удалив цепь из графа, по новой находим все сегменты
            graphWithoutGplane = GetGraphWithoutGplane(faces, graph);

            segments = {};
            GetSegments(faces, graphWithoutGplane, segments);
            RemoveEqualSegments(segments);
        }

    }

    return true;
}

//DFS для поиска мостов в графе
void DFSForBridges( int from,
                    const std::vector<std::vector<int>>& graph,
                    std::vector<bool>& visited,
                    std::vector<int>& timerIn, //Время захода в вершину i во время DFS
                    std::vector<int>& timerUp,
                    std::vector<std::pair<int, int>>& bridges,
                    int parent = -1) {
    static int timer = 0;
    visited[from] = true;
    timerIn[from] = timerUp[from] = timer++;
    for( size_t i = 0; i < graph[from].size(); ++i ) {
        int to = graph[from][i];
        if( to == parent ) {
            continue;
        }
        if( visited[to] ) {
            timerUp[from] = std::min(timerUp[from], timerIn[to]);
        } else {
            DFSForBridges(to, graph, visited, timerIn, timerUp, bridges, from);
            timerUp[from] = std::min(timerUp[from], timerUp[to]);
            if( timerUp[to] > timerIn[from] ) {
                bridges.push_back(std::make_pair(from, to));
                bridges.push_back(std::make_pair(to, from));
            }
        }
    }
};

//Функция поиска мостов
std::vector<std::pair<int, int>> FindBridges(const std::vector<std::vector<int>>& graph) {
    std::vector<bool> visited(graph.size(),false);
    std::vector<int> timerIn(graph.size());
    std::vector<int> timerUp(graph.size(),1e9);
    std::vector<std::pair<int, int>> bridges;
    for( size_t i = 0; i < graph.size(); ++i ) {
        if( !visited[i] ) {
            DFSForBridges(i, graph, visited, timerIn, timerUp, bridges);
        }
    }
    return bridges;
}


//Алгоритм DFS, позволяющий найти компоненты сильной связности. Просто в историю добавляет посещенную вершины
void DFSForComponents(int from, const std::vector<std::vector<int>>& graph, 
    std::vector<bool>& visited, std::vector<int>& history) 
{
    history.push_back(from);
    visited[from] = true;
    for( size_t i = 0; i < graph[from].size(); ++i ) {
        int to = graph[from][i];
        if( !visited[to] ) {
            DFSForComponents(to, graph, visited,history);
        }
    }
}

//Проверяем, прошлись ли мы по вершине во время DFS
bool VertexInHistory(int vertex, const std::vector<int>& history) {
    for( auto v : history ) {
        if( v == vertex ) {
            return true;
        }
    }
    return false;
}

//Из списка ребер получаем список детей для каждой вершины.
std::vector<std::vector<int>> ChangeGraphRealisation(const std::vector<std::pair<int, int>>& component, 
    const std::vector<int>& sortedHistory) 
{
    std::vector<std::vector<int>> newTypeComponent(sortedHistory.size());

    std::unordered_map<int, int> newIndexes;
    int counter = 0;
    for( auto vertex : sortedHistory ) {
        newIndexes[vertex] = counter;
        ++counter;
    }

    for( auto currentEdge : component ) {
        int newIndexForFirstVertex = newIndexes[currentEdge.first];
        int newIndexForSecondVertex = newIndexes[currentEdge.second];
        newTypeComponent[newIndexForFirstVertex].push_back(newIndexForSecondVertex);
    }

    return newTypeComponent;

}

//Из истории обхода DFS'ом получаем вершины, которые находятся в одной компоненте связности. 
//Из них восстанавливаем эту компоненту
std::vector<std::vector<int>> FromHistoryGetComponent(const std::vector<std::vector<int>>& graph, 
    const std::vector<int>& history) 
{
    std::vector<std::pair<int, int>> component;
    for( size_t i = 0; i < graph.size(); ++i ) {
        if( VertexInHistory(i, history) ) {
            for( size_t j = 0; j < graph[i].size(); ++j ) {
                if( VertexInHistory(graph[i][j], history) ) {
                    component.push_back(std::make_pair(i, graph[i][j]));
                }
            }
        }
    }
    std::vector<int> sortedHistory = history;
    std::sort(sortedHistory.begin(), sortedHistory.end());

    std::vector<std::vector<int>> newTypeComponent = ChangeGraphRealisation(component, sortedHistory);
    return newTypeComponent;
}

//Получение всех компонент связности в виде списка отдельных графов. Принимает на вход граф без мостов
std::vector<std::vector<std::vector<int>>> GetAllComponents(const std::vector<std::vector<int>>& graphWithoutBridges) {
    std::vector<std::vector<std::vector<int>>> allComponents;
    std::vector<bool> visited(graphWithoutBridges.size());
    for( size_t i = 0; i < graphWithoutBridges.size(); ++i ) {
        if( !visited[i] ) {
            std::vector<int> history;
            DFSForComponents(i, graphWithoutBridges, visited, history);
            allComponents.push_back(FromHistoryGetComponent(graphWithoutBridges, history));
        }
    }
    return allComponents;
}

//Функция удаление мостов из графа. Возвращает новый граф без мостов. Принимает на вход список мостов.
std::vector<std::vector<int>> GetGraphWithoutBridges(const std::vector<std::vector<int>>& graph, 
    const std::vector<std::pair<int, int>>& bridges) 
{
    std::vector<std::vector<int>> graphWithoutBridges(graph.size());
    for( size_t i = 0; i < graph.size(); ++i ) {
        for( size_t j = 0; j < graph[i].size(); ++j ) {
            bool isBridge = false;
            for( size_t k = 0; k < bridges.size(); ++k ) {
                if( bridges[k].first == static_cast<int>(i) && bridges[k].second == graph[i][j] ) {
                    isBridge = true;
                    break;
                }
            }
            if( !isBridge ) {
                graphWithoutBridges[i].push_back(graph[i][j]);
            }
        }
    }
    return graphWithoutBridges;
}

bool IsPlanar(const std::vector<std::vector<int>>& graph) {
    //Нахождение всех мостов
    std::vector<std::pair<int, int>> bridges = FindBridges(graph);

    //Удаление мостов
    std::vector<std::vector<int>> graphWithoutBridges = GetGraphWithoutBridges(graph, bridges);

    //Нахождение компонент связности
    std::vector<std::vector<std::vector<int>>> allComponents = GetAllComponents(graphWithoutBridges);

    //Решаем задачу для каждой компоненты связности
    bool answer = true;
    for( size_t i = 0; i < allComponents.size(); ++i ) {
        answer &= IsComponentPlanar(allComponents[i]);
    }
    return answer;
}


int main() {
    size_t vertexCount = 0;
    size_t edgeCount = 0;
    std::cin >> vertexCount >> edgeCount;

    std::vector<std::vector<int>> graph(vertexCount);

    int from = 0;
    int to = 0;
    for( size_t i = 0; i < edgeCount; ++i ) {
        std::cin >> from >> to;
        if( from != to ) {
            graph[from].push_back(to);
            graph[to].push_back(from);
        }
    }

    if( IsPlanar(graph) ) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }

    return 0;
}
