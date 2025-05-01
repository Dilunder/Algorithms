#include <iostream>
#include <vector>

using namespace std;

void depthFirstSearch(int currentVertex, vector<int>* visited, vector<vector<int>>* adjacencyList) {
    for (int neighbor : (*adjacencyList)[currentVertex]) {
        if ((*visited)[neighbor] == 0) {
            (*visited)[neighbor] = 1;
            depthFirstSearch(neighbor, visited, adjacencyList);
        }
    }
}

int main() {
    int isLinearGraph = 1;
    int leafCount = 0;

    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    vector<vector<int>> graph(vertexCount + 1);

    for (int i = 0; i < edgeCount; ++i) {
        int vertexA, vertexB;
        cin >> vertexA >> vertexB;
        graph[vertexA].push_back(vertexB);
        graph[vertexB].push_back(vertexA);
    }

    for (int i = 1; i <= vertexCount; ++i) {
        int degree = graph[i].size();

        if (degree == 1) {
            leafCount++;
        }

        if (degree == 0 || degree > 2 || leafCount > 2 || (vertexCount - edgeCount) != 1) {
            isLinearGraph = 0;
            cout << "NO" << endl;
            break;
        }
    }

    if (leafCount == 2 && isLinearGraph) {
        for (int startVertex = 1; startVertex <= vertexCount; ++startVertex) {
            vector<int> visited(vertexCount + 1, 0);
            visited[startVertex] = 1;
            depthFirstSearch(startVertex, &visited, &graph);

            for (int j = 1; j <= vertexCount; ++j) {
                if (visited[j] == 0) {
                    isLinearGraph = 0;
                    cout << "NO" << endl;
                    break;
                }
            }

            if (isLinearGraph) {
                cout << "YES" << endl;
                break;
            }
        }
    }

    return 0;
}