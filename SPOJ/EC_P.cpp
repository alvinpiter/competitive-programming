#include<bits/stdc++.h>
using namespace std;
#define MAXN 700

int T, N, M;
int currentDfsTime, dfsTime[MAXN + 3], minDfsTime[MAXN + 3];
vector<int> adj[MAXN + 3];
vector<pair<int, int> > bridges;

void reset() {
    currentDfsTime = 0;
    bridges.clear();
    for (int i = 0; i <= MAXN; i++) {
        adj[i].clear();
        dfsTime[i] = -1;
    }
}

void DFS(int u, int prv) {
    dfsTime[u] = ++currentDfsTime;
    minDfsTime[u] = dfsTime[u];

    for (auto v: adj[u]) {
        if (v == prv) continue;

        if (dfsTime[v] == -1) {
            //u-v is span-edge
            DFS(v, u);

            minDfsTime[u] = min(minDfsTime[u], minDfsTime[v]);
            if (minDfsTime[v] > dfsTime[u])
                bridges.push_back({min(u, v), max(u, v)});
        } else {
            //u-v is back-edge
            minDfsTime[u] = min(minDfsTime[u], dfsTime[v]);
        }
    }
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        reset();

        cin >> N >> M;
        for (int i = 1; i <= M; i++) {
            int u, v;
            cin >> u >> v;

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        DFS(1, 1);

        cout << "Caso #" << cases << endl;
        if (bridges.size() > 0) {
            sort(bridges.begin(), bridges.end());

            cout << bridges.size() << endl;
            for (auto bridge: bridges)
                cout << bridge.first << " " << bridge.second << endl;
        } else {
            cout << "Sin bloqueos\n";
        }
    }
}
