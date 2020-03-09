#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXLG 18

int n, q, P[MAXN + 3][MAXLG + 3], depth[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS(int u, int prv) {
    for (auto v: adj[u]) {
        if (v != prv) {
            P[v][0] = u;
            depth[v] = depth[u] + 1;
            DFS(v, u);
        }
    }
}

int getKthParent(int x, int k) {
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (k & (1 << lg)) {
            if (x == -1)
                break;
            else
                x = P[x][lg];
        }
    }

    return x;
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v])
        u = getKthParent(u, depth[u] - depth[v]);
    else
        v = getKthParent(v, depth[v] - depth[u]);

    if (u == v)
        return u;

    for (int lg = MAXLG; lg >= 0; lg--) {
        if (P[u][lg] != P[v][lg]) {
            u = P[u][lg];
            v = P[v][lg];
        }
    }

    return P[u][0];
}

int getDistance(int u, int v) {
    int lca = getLCA(u, v);
    return depth[u] + depth[v] - 2 * depth[lca];
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(P, -1, sizeof(P));
    DFS(1, 1);

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= n; i++) {
            if (P[i][lg - 1] != -1)
                P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }

    for (int i = 1; i <= q; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        printf("%d\n", getDistance(a, b));
    }
}
