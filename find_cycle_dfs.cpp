#include <iostream>
#include <vector>

using namespace std;

void depthFirstSearch(int currentVertex, vector<vector<int>>* adjacencyList,
                      vector<int>* parent, vector<int>* visited, bool* hasCycle) {
    (*visited)[currentVertex] = 1;

    for (int neighbor : (*adjacencyList)[currentVertex]) {
        if ((*visited)[neighbor] == 0) {
            (*parent)[neighbor] = currentVertex;
            depthFirstSearch(neighbor, adjacencyList, parent, visited, hasCycle);
        }
        else if ((*visited)[neighbor] == 1 && neighbor != (*parent)[currentVertex]) {
            *hasCycle = true;
        }
    }

    (*visited)[currentVertex] = 2;
}

int main() {
    int verticesCount, edgesCount;
    bool hasCycle = false;
    cin >> verticesCount >> edgesCount;

    vector<vector<int>> adjacencyList(verticesCount + 1);

    for (int i = 0; i < edgesCount; ++i) {
        int vertexA, vertexB;
        cin >> vertexA >> vertexB;
        adjacencyList[vertexA].push_back(vertexB);
        adjacencyList[vertexB].push_back(vertexA);
    }

    for (int vertex = 1; vertex <= verticesCount; ++vertex) {
        if (adjacencyList[vertex].size() < 2) continue;

        vector<int> parent(verticesCount + 1, -1);
        vector<int> visited(verticesCount + 1, 0);

        depthFirstSearch(vertex, &adjacencyList, &parent, &visited, &hasCycle);
        if (hasCycle) break;
    }

    cout << (hasCycle ? "YES" : "NO") << endl;
    return 0;
}