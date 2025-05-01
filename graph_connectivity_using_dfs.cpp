#include <iostream>
#include <vector>

using namespace std;

void dfs(int u, int end, vector<vector<int>> *G, vector<int> *used){
    (*used)[u] = 1;
    for (int i = 0; i < (*G)[u].size(); ++i) {
        if((*used)[end])
            break;
        int to = (*G)[u][i];
        if (to == 0)
            continue;
        if (!(*used)[to])
            dfs(to, end, G, used);
    }
}

int main(){
    int edges, n, zaprosi;
    cin >> edges >> n >> zaprosi;
    vector<vector<int>> G(edges + 1);
    int x, y;
    for (int i = 1; i < edges + 1; ++i) {
        G[i].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    string symbol, edge_from, edge_to;
    int from, to;
    for (int i = 0; i < zaprosi; ++i) {
        cin >> symbol >> edge_from >> edge_to;
        from = stoi(edge_from);
        to = stoi(edge_to);
        vector<int>used (edges + 1, 0);
        dfs(from, to, &G, &used);
        if (symbol == "-"){
            for (int j = 0; j < G[from].size(); ++j) {
                if (G[from][j] == to)
                    G[from][j] = 0;
            }
            for (int j = 0; j < G[to].size(); ++j) {
                if (G[to][j] == from)
                    G[to][j] = 0;
            }
        }
        else{
            if (used[from] && used[to])
                cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        used.clear();
    }
    return 0;
}