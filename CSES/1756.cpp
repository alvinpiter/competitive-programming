#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXM 200000

int N, M, tin[MAXN + 3], dfsTime;
pair<int, int> edges[MAXM + 3];
vector<int> adj[MAXN + 3];

void DFS(int u) {
    tin[u] = ++dfsTime;
    for (auto v: adj[u]) {
        if (tin[v] == -1) {
            DFS(v);
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        edges[i] = {u, v};
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfsTime = 0;
    memset(tin, -1, sizeof(tin));

    for (int i = 1; i <= N; i++) {
        if (tin[i] == -1)
            DFS(i);
    }

    for (int i = 1; i <= M; i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        if (tin[u] < tin[v])
            cout << u << " " << v << endl;
        else
            cout << v << " " << u << endl;
    }
}
