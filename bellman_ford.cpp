#include <iostream>
#include <vector>
#include <climits>

using namespace std;

static const int INFINITY_VALUE = INT_MAX / 2;

void findNegativeCycles(vector<vector<int>>& edges, int vertexCount, int edgeCount, int maxCycleLength) {
    vector<int> distances(vertexCount, INFINITY_VALUE);
    vector<int> predecessors(vertexCount, -1);
    distances[0] = 0;

    int lastRelaxedVertex = -1;
    bool wasRelaxed;

    for (int i = 0; i < vertexCount; i++) {
        lastRelaxedVertex = -1;
        wasRelaxed = false;

        for (int j = 0; j < edgeCount; j++) {
            int from = edges[j][0];
            int to = edges[j][1];
            int weight = edges[j][2];

            if (distances[to] > distances[from] + weight) {
                distances[to] = max(-INFINITY_VALUE, distances[from] + weight);
                predecessors[to] = from;
                lastRelaxedVertex = to;
                wasRelaxed = true;
            }
        }

        if (!wasRelaxed)
            break;
    }

    if (lastRelaxedVertex == -1) {
        cout << "YES" << endl;
    } else {
        int cycleVertex = lastRelaxedVertex;
        for (int i = 0; i < vertexCount; i++) {
            cycleVertex = predecessors[cycleVertex];
        }

        vector<int> cycle;
        for (int current = cycleVertex; ; current = predecessors[current]) {
            cycle.push_back(current);
            if (current == cycleVertex && cycle.size() > 1) {
                break;
            }
        }

        if (cycle.size() - 1 < maxCycleLength) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    int testCasesCount, maxAllowedCycleLength;
    cin >> testCasesCount >> maxAllowedCycleLength;

    vector<vector<int>> graphEdges;
    int vertexCount, edgeCount;

    for (int i = 0; i < testCasesCount; ++i) {
        cin >> vertexCount >> edgeCount;
        for (int j = 0; j < edgeCount; ++j) {
            int from, to, weight;
            cin >> from >> to >> weight;
            graphEdges.push_back({from - 1, to - 1, weight});
        }
        findNegativeCycles(graphEdges, vertexCount, edgeCount, maxAllowedCycleLength);
        graphEdges.clear();
    }
    return 0;
}
