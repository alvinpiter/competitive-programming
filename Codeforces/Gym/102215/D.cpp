#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXLG 18

/*
Find LCA of all red nodes, name it lcaRed
Find LCA of all blue nodes, name it lcaBlue

One of these two statements must be true:
* There must be no blue node below lcaRed
* There must be no red node below lcaBlue

To check if a node is below some node, check its dfsTime.
*/

int n, q;
int dfsTime, tin[MAXN + 3], tout[MAXN + 3], depth[MAXN + 3], P[MAXN + 3][MAXLG + 3];
vector<int> adj[MAXN + 3];
int nr, nb, red[MAXN + 3], blue[MAXN + 3];

void DFS(int u, int prv) {
    tin[u] = ++dfsTime;
    for (auto v: adj[u]) {
        if (v != prv) {
            P[v][0] = u;
            depth[v] = depth[u] + 1;
            DFS(v, u);
        }
    }
    tout[u] = dfsTime;
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (diff & (1 << lg))
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

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;

        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(P, 0, sizeof(P));

    depth[1] = 0;
    P[1][0] = 0;
    dfsTime = 0;
    DFS(1, 0);

    //Init LCA
    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= n; i++) {
            P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }

    scanf("%d", &q);
    for (int query = 1; query <= q; query++) {
        scanf("%d%d", &nr, &nb);

        for (int i = 1; i <= nr; i++)
            scanf("%d", &red[i]);

        for (int i = 1; i <= nb; i++)
            scanf("%d", &blue[i]);

        int lcaRed = red[1];
        for (int i = 1; i <= nr; i++)
            lcaRed = getLCA(lcaRed, red[i]);

        int lcaBlue = blue[1];
        for (int i = 1; i <= nb; i++)
            lcaBlue = getLCA(lcaBlue, blue[i]);

        bool onlyRed = true; //Only red below lcaRed
        for (int i = 1; i <= nb; i++) {
            if (tin[blue[i]] >= tin[lcaRed] && tin[blue[i]] <= tout[lcaRed])
                onlyRed = false;
        }

        bool onlyBlue = true; //Only blue below lcaBlue
        for (int i = 1; i <= nr; i++) {
            if (tin[red[i]] >= tin[lcaBlue] && tin[red[i]] <= tout[lcaBlue])
                onlyBlue = false;
        }

        if (onlyRed || onlyBlue)
            printf("YES\n");
        else
            printf("NO\n");
    }
}
