#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> Edge;
typedef vector<vector<Edge>> Graph;

void findShortestPaths(Graph& graph, vector<int>& distances, int startVertex) {
    priority_queue<Edge, vector<Edge>, greater<Edge>> priorityQueue;
    priorityQueue.push(make_pair(0, startVertex));

    while (!priorityQueue.empty()) {
        int currentVertex = priorityQueue.top().second;
        int currentDistance = priorityQueue.top().first;
        priorityQueue.pop();

        if (currentDistance > distances[currentVertex]) continue;

        for (const Edge& neighbor : graph[currentVertex]) {
            int neighborVertex = neighbor.first;
            int edgeWeight = neighbor.second;

            if (distances[neighborVertex] > distances[currentVertex] + edgeWeight) {
                distances[neighborVertex] = distances[currentVertex] + edgeWeight;
                priorityQueue.push(make_pair(distances[neighborVertex], neighborVertex));
            }
        }
    }
}

int main() {
    int verticesCount, edgesCount, queriesCount, startVertex;
    cin >> verticesCount >> edgesCount >> queriesCount >> startVertex;

    Graph graph(verticesCount);
    vector<int> distances(verticesCount, INT_MAX);
    distances[startVertex - 1] = 0;

    for (int i = 0; i < edgesCount; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from - 1].push_back(make_pair(to - 1, weight));
        graph[to - 1].push_back(make_pair(from - 1, weight));
    }

    findShortestPaths(graph, distances, startVertex - 1);

    for (int i = 0; i < queriesCount; ++i) {
        int targetVertex;
        cin >> targetVertex;
        if (distances[targetVertex - 1] == INT_MAX) {
            cout << -1 << endl;
        } else {
            cout << distances[targetVertex - 1] << endl;
        }
    }

    return 0;
}