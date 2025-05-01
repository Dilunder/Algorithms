#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

/**
 * Поиск увеличивающего пути с помощью BFS
 * @param source Исток
 * @param sink Сток
 * @param parent Массив для хранения пути
 * @param adjacencyList Список смежности графа
 * @param numVertices Количество вершин
 * @param capacity Матрица пропускных способностей
 * @return true если путь от истока к стоку существует
 */
bool findAugmentingPath(int source, int sink, vector<int>& parent,
                        const vector<vector<int>>& adjacencyList,
                        int numVertices,
                        const vector<vector<int>>& capacity) {
    vector<bool> visited(numVertices + 1, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : adjacencyList[current]) {
            if (!visited[neighbor] && capacity[current][neighbor] > 0) {
                visited[neighbor] = true;
                q.push(neighbor);
                parent[neighbor] = current;
            }
        }
    }
    return visited[sink];
}

/**
 * Алгоритм Форда-Фалкерсона для поиска максимального потока
 * @param source Исток
 * @param sink Сток
 * @param adjacencyList Список смежности графа
 * @param numVertices Количество вершин
 * @param capacity Матрица пропускных способностей (будет изменена)
 * @return Значение максимального потока
 */
int computeMaxFlow(int source, int sink, vector<vector<int>>& adjacencyList,
                   int numVertices, vector<vector<int>>& capacity) {
    vector<int> parent(numVertices + 1);
    int maxFlow = 0;

    while (findAugmentingPath(source, sink, parent, adjacencyList, numVertices, capacity)) {
        int pathFlow = INT_MAX;

        // Находим минимальную пропускную способность в пути
        for (int vertex = sink; vertex != source; vertex = parent[vertex]) {
            int previous = parent[vertex];
            pathFlow = min(pathFlow, capacity[previous][vertex]);
        }

        // Обновляем пропускные способности
        for (int vertex = sink; vertex != source; vertex = parent[vertex]) {
            int previous = parent[vertex];
            capacity[previous][vertex] -= pathFlow;
            capacity[vertex][previous] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;
    int source = 1, sink = numVertices;

    vector<vector<int>> adjacencyList(numVertices + 1);
    vector<vector<int>> capacity(numVertices + 1, vector<int>(numVertices + 1, 0));

    // Чтение входных данных
    for (int i = 1; i <= numEdges; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        adjacencyList[from].push_back(to);
        capacity[from][to] = weight;
    }

    cout << computeMaxFlow(source, sink, adjacencyList, numVertices, capacity) << endl;
    return 0;
}