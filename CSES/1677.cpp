#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, Q, parent[MAXN + 3], numComponent, answer[2 * MAXN + 3];
pair<int, int> queries[2 * MAXN + 3];
set<int> adj[MAXN + 3];

int findSet(int u) {
    return (parent[u] == u ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return (findSet(u) == findSet(v));
}

void joinSet(int u, int v) {
    if (!isSameSet(u, v)) {
        numComponent -= 1;
        parent[findSet(u)] = findSet(v);
    }
}

int main() {
    cin >> N >> M >> Q;
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    for (int i = 1; i <= Q; i++) {
        int u, v;
        cin >> u >> v;

        queries[i] = {u, v};

        adj[u].erase(v);
        adj[v].erase(u);
    }

    numComponent = N;
    for (int i = 1; i <= N; i++)
        parent[i] = i;

    for (int u = 1; u <= N; u++) {
        for (auto v: adj[u]) {
            joinSet(u, v);
        }
    }

    //Process queries backward
    for (int q = Q; q >= 1; q--) {
        answer[q] = numComponent;
        joinSet(queries[q].first, queries[q].second);
    }

    for (int i = 1; i <= Q; i++) {
        if (i > 1)
            cout << " ";

        cout << answer[i];
    }
    cout << endl;
}
