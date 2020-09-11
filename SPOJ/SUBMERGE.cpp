#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000
#define ROOT 1

int N, M;
int currentDfsTime, dfsTime[MAXN + 3], minDfsTime[MAXN + 3], articulationPointCount;
vector<int> adj[MAXN + 3];

void reset() {
    currentDfsTime = 0;
    for (int i = 1; i <= MAXN; i++) {
        adj[i].clear();
        dfsTime[i] = -1;
    }

    articulationPointCount = 0;
}

void DFS(int u, int p) {
    dfsTime[u] = ++currentDfsTime;
    minDfsTime[u] = dfsTime[u];

    bool isArticulationPoint = false;
    int spanEdgeFromRootCount = 0; //How many span edge originating from root (node 1).
    for (auto v: adj[u]) {
        if (v == p) continue;

        if (dfsTime[v] == -1) {
            DFS(v, u);
            minDfsTime[u] = min(minDfsTime[u], minDfsTime[v]);

            if (u == ROOT) {
                spanEdgeFromRootCount += 1;
            } else {
                if (minDfsTime[v] >= dfsTime[u])
                    isArticulationPoint = true;
            }
        } else {
            minDfsTime[u] = min(minDfsTime[u], dfsTime[v]);
        }
    }

    if (u == ROOT) {
        if (spanEdgeFromRootCount > 1)
            articulationPointCount += 1;
    } else {
        if (isArticulationPoint)
            articulationPointCount += 1;
    }
}

int main() {
    while (true) {
        cin >> N >> M;
        if (N == 0 && M == 0)
            break;

        reset();

        for (int i =  1; i <= M; i++) {
            int u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        DFS(ROOT, ROOT);

        cout << articulationPointCount << endl;
    }
}
