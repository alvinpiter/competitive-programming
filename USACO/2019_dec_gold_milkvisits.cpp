#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXLG 17

/*
Euler tour. For each type, keep track on when DFS visits/leaves it.
Whenever we visit a type, add +1 and whenever we leave a type, add -1.
The prefix sum will equal to number of this type we encounter if we walk from root to a node.
*/

int N, M, typ[MAXN + 3];
vector<int> adj[MAXN + 3];

//DFS variables
int dfsTime, tin[MAXN + 3];
vector<pair<int, int> > occ[MAXN + 3];

//LCA variables
int P[MAXN + 3][MAXLG + 3], depth[MAXN + 3];

void DFS(int u, int prv) {
    tin[u] = ++dfsTime;
    occ[typ[u]].push_back({1, tin[u]});

    for (auto v: adj[u]) {
        if (v != prv) {
            P[v][0] = u;
            depth[v] = depth[u] + 1;
            DFS(v, u);
        }
    }

    ++dfsTime;
    occ[typ[u]].push_back({-1, dfsTime});
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (diff&(1 << lg))
            v = P[v][lg];
    }

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

int getLb(int t, int dfstime) {
    int lo = 0, hi = (int) occ[t].size() - 1, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (occ[t][mid].second < dfstime)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return lo;
}

int getOccurence(int t, int from, int to) {
    int l = getLb(t, from);
    int r = getLb(t, to + 1) - 1;

    if (l == (int) occ[t].size() || l > r)
        return 0;
    else
        return occ[t][r].first - (l == 0 ? 0 : occ[t][l - 1].first);
}

int main() {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &typ[i]);

    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(P, 0, sizeof(P));
    dfsTime = 0;
    depth[1] = 0;

    DFS(1, 1);

    //Initialize LCA
    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }

    //prefix sum
    for (int t = 1; t <= N; t++) {
        for (int i = 1; i < (int) occ[t].size(); i++)
            occ[t][i].first += occ[t][i - 1].first;
    }

    for (int i = 1; i <= M; i++) {
        int u, v, t;
        scanf("%d%d%d", &u, &v, &t);

        int lca = getLCA(u, v);
        int cnt = getOccurence(t, tin[lca], tin[u]) + getOccurence(t, tin[lca], tin[v]);

        if (cnt > 0)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}
