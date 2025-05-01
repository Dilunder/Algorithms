#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

using Vertex = int;
using Weight = int;
using Edge = pair<Vertex, Weight>;
using Graph = vector<vector<Edge>>;
using PriorityQueue = priority_queue<pair<Weight, Vertex>, vector<pair<Weight, Vertex>>, greater<pair<Weight, Vertex>>>;

const Weight INFINITY_WEIGHT = INT_MAX;

Weight findShortestPath(Graph& graph, Vertex start, Vertex target, int vertexCount) {
    vector<Weight> distances(vertexCount, INFINITY_WEIGHT);
    distances[start] = 0;

    PriorityQueue minHeap;
    minHeap.push({0, start});

    while (!minHeap.empty()) {
        Vertex currentVertex = minHeap.top().second;
        Weight currentDistance = minHeap.top().first;
        minHeap.pop();

        if (currentDistance > distances[currentVertex]) {
            continue;
        }

        for (const Edge& edge : graph[currentVertex]) {
            Vertex neighbor = edge.first;
            Weight edgeWeight = edge.second;
            Weight newDistance = distances[currentVertex] + edgeWeight;

            if (newDistance < distances[neighbor]) {
                distances[neighbor] = newDistance;
                minHeap.push({newDistance, neighbor});
            }
        }
    }

    return distances[target] == INFINITY_WEIGHT ? -1 : distances[target];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    int startVertex, targetVertex;
    cin >> startVertex >> targetVertex;

    Graph graph(vertexCount);

    for (int i = 0; i < edgeCount; ++i) {
        Vertex from, to;
        Weight weight;
        cin >> from >> to >> weight;
        graph[from - 1].emplace_back(to - 1, weight);
    }

    Weight shortestPathLength = findShortestPath(graph, startVertex - 1, targetVertex - 1, vertexCount);
    cout << shortestPathLength << endl;

    return 0;
}