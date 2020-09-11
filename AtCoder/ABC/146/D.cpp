#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, inDegree[MAXN + 3], K, answer[MAXN + 3];
vector<pair<int, int> > adj[MAXN + 3]; //(v, idx)

void DFS(int u, int prvNode, int prvColor) {
    int ptrColor = 1;
    for (auto e: adj[u]) {
        int v = e.first, id = e.second;

        if (v == prvNode) continue;

        if (ptrColor == prvColor)
            ptrColor += 1;

        answer[id] = ptrColor;
        DFS(v, u, answer[id]);

        ptrColor += 1;
    }
}

int main() {
    cin >> N;

    memset(inDegree, 0, sizeof(inDegree));
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back({v, i});
        adj[v].push_back({u, i});

        inDegree[u] += 1;
        inDegree[v] += 1;
    }

    K = 0;
    for (int i = 1; i <= N; i++)
        K = max(K, inDegree[i]);

    DFS(1, -1, -1);

    cout << K << endl;
    for (int i = 1; i < N; i++)
        cout << answer[i] << endl;
}
