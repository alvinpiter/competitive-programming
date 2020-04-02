#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXLG 18

int N, M, v[MAXN + 3];
int depth[MAXN + 3], P[MAXN + 3][MAXLG + 3];
vector<int> adj[MAXN + 3];

void DFS(int u, int prv) {
    for (auto v: adj[u]) {
        if (v != prv) {
            depth[v] = depth[u] + 1;
            P[v][0] = u;

            DFS(v, u);
        }
    }
}

void initLCA() {
    memset(P, -1, sizeof(P));

    depth[1] = 0;
    DFS(1, 1);

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            if (P[i][lg - 1] != -1)
                P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);

    int diff = depth[v] - depth[u];
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (diff & (1 << lg))
            v = P[v][lg];
    }

    if (u == v) return u;

    for (int lg = MAXLG; lg >= 0; lg--) {
        if (P[u][lg] != P[v][lg]) {
            u = P[u][lg];
            v = P[v][lg];
        }
    }

    return P[u][0];
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    initLCA();

    for (int q = 1; q <= M; q++) {
        int k, deepest = 1;

        scanf("%d", &k);
        for (int i = 1; i <= k; i++) {
            scanf("%d", &v[i]);
            if (depth[v[i]] > depth[deepest])
                deepest = v[i];
        }

        bool valid = true;
        for (int i = 1; i <= k; i++) {
            if (getLCA(deepest, v[i]) != v[i] && getLCA(deepest, P[v[i]][0]) != P[v[i]][0])
                valid = false;
        }

        if (valid)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
