#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define DEBUG true

/*
dfsTime[u] = When node u is visited by DFS
minDfsTime[u] = Minimum dfsTime reachable from u using at most 1 back-edge
*/

int N, M, currentDfsTime, dfsTime[MAXN + 3], minDfsTime[MAXN + 3], parent[MAXN + 3], bridgeCount;
vector<int> adj[MAXN + 3];
set<pair<int, int> > directedEdges;

void DFS(int u) {
    dfsTime[u] = ++currentDfsTime;
    minDfsTime[u] = dfsTime[u];

    for (auto v: adj[u]) {
        if (v == parent[u]) continue;

        if (dfsTime[v] == -1) {
            //u-v is span-edge
            parent[v] = u;
            DFS(v);

            minDfsTime[u] = min(minDfsTime[u], minDfsTime[v]);
            directedEdges.insert({u, v});

            if (minDfsTime[v] > dfsTime[u]) {
                bridgeCount += 1;
            }
        } else {
            //u-v is back-edge

            if (dfsTime[v] < dfsTime[u])
                directedEdges.insert({u, v});

            minDfsTime[u] = min(minDfsTime[u], dfsTime[v]);
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(parent, -1, sizeof(parent));
    memset(dfsTime, -1, sizeof(dfsTime));

    currentDfsTime = 0;
    DFS(1);

    if (bridgeCount > 0) {
        cout << 0 << endl;
    } else {
        for (auto edge: directedEdges)
            cout << edge.first << " " << edge.second << endl;
    }
}
