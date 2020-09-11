#include<bits/stdc++.h>
using namespace std;
#define MAXN 300000

int n, m, q, parent[MAXN + 3], diameter[MAXN + 3], dist[MAXN + 3], dist2[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS(int u, int d[], int& furthest) {
    for (auto v: adj[u]) {
        if (d[v] == -1) {
            d[v] = d[u] + 1;
            if (d[v] > d[furthest])
                furthest = v;

            DFS(v, d, furthest);
        }
    }
}

int findDiameter(int u) {
    int furthest = u;
    dist[u] = 0;
    DFS(u, dist, furthest);

    int furthest2 = furthest;
    dist2[furthest] = 0;
    DFS(furthest, dist2, furthest2);

    return dist2[furthest2];
}

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}

void joinSet(int u, int v, bool shouldMinimizeDiameter) {
    if (isSameSet(u, v))
        return;
    else {
        int pu = findSet(u);
        int pv = findSet(v);

        parent[pv] = pu;

        if (shouldMinimizeDiameter) {
            int du = diameter[pu];
            int dv = diameter[pv];

            diameter[pu] = max(max(du, dv), (du + 1)/2 + (dv + 1)/2 + 1);
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        diameter[i] = -1;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);

        joinSet(u, v, false);
    }

    memset(dist, -1, sizeof(dist));
    memset(dist2, -1, sizeof(dist2));
    for (int u = 1; u <= n; u++) {
        int pu = findSet(u);
        if (diameter[pu] == -1)
            diameter[pu] = findDiameter(pu);
    }

    for (int i = 1; i <= q; i++) {
        int t, x, y;

        scanf("%d", &t);
        if (t == 1) {
            scanf("%d", &x);
            printf("%d\n", diameter[findSet(x)]);
        } else {
            scanf("%d%d", &x, &y);
            joinSet(x, y, true);
        }
    }
}
