#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int weight;
    int from;
    int to;
    int index;
    bool in_mst;
};

struct DisjointSet {
    int parent;
    int rank;
};

int findRoot(int vertex, vector<DisjointSet>& dsu) {
    if (vertex != dsu[vertex].parent) {
        dsu[vertex].parent = findRoot(dsu[vertex].parent, dsu);
    }
    return dsu[vertex].parent;
}

void unionSets(int a, int b, vector<DisjointSet>& dsu) {
    a = findRoot(a, dsu);
    b = findRoot(b, dsu);

    if (a != b) {
        if (dsu[a].rank < dsu[b].rank) {
            swap(a, b);
        }
        dsu[b].parent = a;
        if (dsu[a].rank == dsu[b].rank) {
            dsu[a].rank++;
        }
    }
}

void processGraph(int vertexCount, int edgeCount) {
    vector<Edge> edges(edgeCount);
    vector<Edge> mstEdges;
    vector<DisjointSet> dsu(vertexCount);

    for (int i = 0; i < edgeCount; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;
        edges[i].from--;
        edges[i].to--;
        edges[i].index = i;
        edges[i].in_mst = false;
    }

    for (int i = 0; i < vertexCount; ++i) {
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    // Построение MST (алгоритм Крускала)
    int mstCost = 0;
    for (const Edge& edge : edges) {
        int rootFrom = findRoot(edge.from, dsu);
        int rootTo = findRoot(edge.to, dsu);

        if (rootFrom != rootTo) {
            mstCost += edge.weight;
            unionSets(edge.from, edge.to, dsu);
            mstEdges.push_back(edge);

            if (mstEdges.size() == vertexCount - 1) {
                break;
            }
        }
    }

    for (const Edge& edge : edges) {
        if (edge.in_mst) {
            cout << mstCost << '\n';
            continue;
        }

        vector<DisjointSet> tempDsu = dsu;
        int tempCost = mstCost + edge.weight;

        unionSets(edge.from, edge.to, tempDsu);

        for (const Edge& mstEdge : mstEdges) {
            int rootFrom = findRoot(mstEdge.from, tempDsu);
            int rootTo = findRoot(mstEdge.to, tempDsu);

            if (rootFrom != rootTo) {
                tempCost -= mstEdge.weight;
                unionSets(mstEdge.from, mstEdge.to, tempDsu);
            }
        }

        cout << tempCost << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    processGraph(vertexCount, edgeCount);

    return 0;
}