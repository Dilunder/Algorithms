#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacency_list;
    int vertex_count;
    int edge_count;

public:
    Graph(int vertices, int edges) : vertex_count(vertices), edge_count(edges) {
        adjacency_list.resize(vertex_count + 1); // +1 для 1-based индексации
    }

    void addEdge(int from, int to) {
        adjacency_list[from].push_back(to);
        adjacency_list[to].push_back(from); // Для неориентированного графа
    }

    int findShortestPath(int start, int destination) {
        vector<int> distances(vertex_count + 1, -1); // Инициализируем расстояния
        queue<int> bfs_queue;

        distances[start] = 0;
        bfs_queue.push(start);

        while (!bfs_queue.empty()) {
            int current_vertex = bfs_queue.front();
            bfs_queue.pop();

            // Проверяем всех соседей текущей вершины
            for (int neighbor : adjacency_list[current_vertex]) {
                if (distances[neighbor] == -1) { // Если вершина еще не посещена
                    distances[neighbor] = distances[current_vertex] + 1;
                    bfs_queue.push(neighbor);

                    // Если достигли цели, можно сразу вернуть результат
                    if (neighbor == destination) {
                        return distances[destination];
                    }
                }
            }
        }

        return distances[destination]; // Вернет -1 если путь не найден
    }
};

int main() {
    int vertex_count, edge_count;
    cin >> vertex_count >> edge_count;

    Graph graph(vertex_count, edge_count);

    // Чтение ребер графа
    for (int i = 0; i < edge_count; ++i) {
        int from, to;
        cin >> from >> to;
        graph.addEdge(from, to);
    }

    int start_vertex, destination_vertex;
    cin >> start_vertex >> destination_vertex;

    int shortest_path_length = graph.findShortestPath(start_vertex, destination_vertex);

    if (shortest_path_length == -1) {
        cout << -1 << endl;
    } else {
        cout << shortest_path_length << endl;
    }

    return 0;
}