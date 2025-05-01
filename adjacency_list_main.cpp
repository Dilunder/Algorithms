#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct QueueNode {
    int vertex;
    QueueNode* next;
};

class BfsQueue {
private:
    QueueNode* front_;
    QueueNode* rear_;

public:
    BfsQueue() : front_(nullptr), rear_(nullptr) {}

    void enqueue(int vertex) {
        QueueNode* newNode = new QueueNode;
        newNode->vertex = vertex;
        newNode->next = nullptr;

        if (isEmpty()) {
            front_ = rear_ = newNode;
        } else {
            rear_->next = newNode;
            rear_ = newNode;
        }
    }

    void dequeue() {
        if (!isEmpty()) {
            QueueNode* temp = front_;
            front_ = front_->next;
            delete temp;
        }
    }

    int getFront() const {
        return front_->vertex;
    }

    bool isEmpty() const {
        return front_ == nullptr;
    }
};

int main() {
    int totalVertices, totalEdges;
    cin >> totalVertices >> totalEdges;

    vector<vector<int>> adjacencyList(totalVertices);

    for (int i = 0; i < totalEdges; ++i) {
        int from, to;
        cin >> from >> to;
        adjacencyList[from].push_back(to);
        adjacencyList[to].push_back(from);
    }

    vector<int> visited(totalVertices, 0);
    vector<int> distance(totalVertices, 0);
    vector<int> parent(totalVertices, -1);

    const int startVertex = 0;
    visited[startVertex] = 1;
    distance[startVertex] = 0;
    parent[startVertex] = -1;

    BfsQueue bfsQueue;
    bfsQueue.enqueue(startVertex);

    while (!bfsQueue.isEmpty()) {
        int currentVertex = bfsQueue.getFront();
        bfsQueue.dequeue();

        for (int neighbor : adjacencyList[currentVertex]) {
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                distance[neighbor] = distance[currentVertex] + 1;
                parent[neighbor] = currentVertex;
                bfsQueue.enqueue(neighbor);
            }
        }
    }

    cout << "Расстояния от вершины " << startVertex << ":\n";
    for (int i = 0; i < totalVertices; ++i) {
        cout << distance[i] << " ";
    }
    cout << endl;

    const int targetVertex = 5;
    vector<int> path;

    if (!visited[targetVertex]) {
        cout << "Путь до вершины " << targetVertex << " не существует" << endl;
    } else {
        for (int vertex = targetVertex; vertex != -1; vertex = parent[vertex]) {
            path.push_back(vertex);
        }
        reverse(path.begin(), path.end());

        cout << "Путь до вершины " << targetVertex << ": ";
        for (int vertex : path) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}