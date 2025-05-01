#include <iostream>
#include <vector>
#include <algorithm>

// KruskalAlgorithm - поиск 2-х MST

using namespace std;

int findRoot(int node, vector<int>& parent) {
    if (node == parent[node])
        return node;
    return parent[node] = findRoot(parent[node], parent);
}

void uniteSets(int node1, int node2, vector<int>& parent) {
    node1 = findRoot(node1, parent);
    node2 = findRoot(node2, parent);
    if (node1 != node2)
        parent[node1] = node2;
}

int main() {
    int verticesCount, edgesCount;
    cin >> verticesCount >> edgesCount;

    vector<pair<int, pair<int, int>>> edges;
    vector<int> parent(verticesCount);
    vector<pair<int, pair<int, int>>> mstEdges;

    for (int i = 0; i < edgesCount; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        edges.push_back({weight, {from - 1, to - 1}});
    }

    for (int i = 0; i < verticesCount; i++)
        parent[i] = i;

    sort(edges.begin(), edges.end());

    int totalWeight = 0;
    for(const auto& edge : edges) {
        int from = edge.second.first;
        int to = edge.second.second;
        int weight = edge.first;

        if (findRoot(from, parent) != findRoot(to, parent)) {
            totalWeight += weight;
            mstEdges.push_back(edge);
            uniteSets(from, to, parent);
        }
    }

    cout << totalWeight << ' ';

    int secondBestWeight = INT_MAX;
    for (const auto& excludedEdge : mstEdges) {
        for (int i = 0; i < verticesCount; i++)
            parent[i] = i;

        int currentWeight = 0;
        for (const auto& edge : edges) {
            int from = edge.second.first;
            int to = edge.second.second;
            int weight = edge.first;

            if (edge == excludedEdge)
                continue;

            if (findRoot(from, parent) != findRoot(to, parent)) {
                currentWeight += weight;
                uniteSets(from, to, parent);
            }
        }

        if (currentWeight < secondBestWeight)
            secondBestWeight = currentWeight;
    }

    cout << secondBestWeight << endl;
    return 0;
}