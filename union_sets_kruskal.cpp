#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findRoot(int vertex, vector<int>& parent) {
    if (vertex != parent[vertex]) {
        parent[vertex] = findRoot(parent[vertex], parent);
    }
    return parent[vertex];
}

void unionSets(int set_a, int set_b, vector<int>& parent) {
    set_a = findRoot(set_a, parent);
    set_b = findRoot(set_b, parent);

    if (set_a != set_b) {
        parent[set_a] = set_b;
    }
}

int main() {
    int vertices_count, edges_count;
    cin >> vertices_count >> edges_count;

    vector<pair<long, pair<int, int>>> edges;
    vector<int> parent(vertices_count);

    for (int i = 0; i < edges_count; i++) {
        int vertex_a, vertex_b;
        long weight;
        cin >> vertex_a >> vertex_b >> weight;

        if (vertex_a < vertex_b) {
            edges.emplace_back(weight, make_pair(vertex_a - 1, vertex_b - 1));
        } else {
            edges.emplace_back(weight, make_pair(vertex_b - 1, vertex_a - 1));
        }
    }

    for (int i = 0; i < vertices_count; i++) {
        parent[i] = i;
    }

    sort(edges.begin(), edges.end());

    long total_weight = 0;

    // Алгоритм Крускала
    for (const auto& edge : edges) {
        int vertex_a = edge.second.first;
        int vertex_b = edge.second.second;
        long weight = edge.first;

        if (findRoot(vertex_a, parent) != findRoot(vertex_b, parent)) {
            total_weight += weight;
            unionSets(vertex_a, vertex_b, parent);
        }
    }

    cout << total_weight << '\n';
    return 0;
}