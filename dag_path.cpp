#include <iostream>
#include <list>
#include <stack>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class GraphNode {
    int destination;
    int edgeWeight;
public:
    GraphNode(int dest, int weight) : destination(dest), edgeWeight(weight) {}
    int getDestination() const { return destination; }
    int getWeight() const { return edgeWeight; }
};

class DirectedGraph {
    int verticesCount;
    list<GraphNode>* adjacencyList;

    void topologicalSortHelper(int vertex, bool visited[], stack<int>& topologicalOrder);
public:
    DirectedGraph(int vertices);
    ~DirectedGraph();
    void addDirectedEdge(int source, int destination, int weight);
    void findShortestPath(int startVertex, int endVertex);
};

DirectedGraph::DirectedGraph(int vertices) : verticesCount(vertices) {
    adjacencyList = new list<GraphNode>[vertices];
}

DirectedGraph::~DirectedGraph() {
    delete[] adjacencyList;
}

void DirectedGraph::addDirectedEdge(int source, int destination, int weight) {
    adjacencyList[source].push_back(GraphNode(destination, weight));
}

void DirectedGraph::topologicalSortHelper(int vertex, bool visited[], stack<int>& topologicalOrder) {
    visited[vertex] = true;

    for (const auto& node : adjacencyList[vertex]) {
        if (!visited[node.getDestination()]) {
            topologicalSortHelper(node.getDestination(), visited, topologicalOrder);
        }
    }

    topologicalOrder.push(vertex);
}

void DirectedGraph::findShortestPath(int startVertex, int endVertex) {
    stack<int> topologicalOrder;
    bool* visited = new bool[verticesCount]();
    int* distances = new int[verticesCount];

    for (int i = 0; i < verticesCount; ++i) {
        distances[i] = INF;
    }
    distances[startVertex] = 0;

    for (int i = 0; i < verticesCount; ++i) {
        if (!visited[i]) {
            topologicalSortHelper(i, visited, topologicalOrder);
        }
    }

    while (!topologicalOrder.empty()) {
        int currentVertex = topologicalOrder.top();
        topologicalOrder.pop();

        if (distances[currentVertex] != INF) {
            for (const auto& node : adjacencyList[currentVertex]) {
                int neighbor = node.getDestination();
                int newDistance = distances[currentVertex] + node.getWeight();

                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                }
            }
        }
    }

    if (distances[endVertex] == INF) {
        cout << -1 << endl;
    } else {
        cout << distances[endVertex] << endl;
    }

    delete[] visited;
    delete[] distances;
}

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    int startVertex, endVertex;
    cin >> startVertex >> endVertex;

    DirectedGraph graph(vertices);

    for (int i = 0; i < edges; ++i) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph.addDirectedEdge(source - 1, destination - 1, weight);
    }

    graph.findShortestPath(startVertex - 1, endVertex - 1);
    return 0;
}