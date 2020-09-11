#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXLG 17

/*
Build segment tree on DFS order of nodes.
*/

class SegmentTree {
private:
    int SZ, tree[4 * 2 * MAXN + 3];

    void update(int node, int l, int r, int idx, int val) {
        if (r < idx || l > idx)
            return;

        if (l == r) {
            tree[node] = val;
            return;
        }

        int m = (l + r)/2;
        update(2 * node, l, m, idx, val);
        update(2 * node + 1, m + 1, r, idx, val);

        tree[node] = tree[2 * node] ^ tree[2 * node + 1];
    }

    int query(int node, int l, int r, int le, int ri) {
        if (r < le || l > ri)
            return 0;

        if (l >= le && r <= ri)
            return tree[node];

        int m = (l + r)/2;
        return (
            query(2 * node, l, m, le, ri) ^
            query(2 * node + 1, m + 1, r, le, ri)
        );
    }
public:
    SegmentTree(int sz) {
        SZ = sz;
        memset(tree, 0, sizeof(tree));
    }

    void update(int idx, int val) {
        update(1, 1, SZ, idx, val);
    }

    int query(int l, int r) {
        return query(1, 1, SZ, l, r);
    }
};

int N, Q, e[MAXN + 3];

//DFS variables
int dfsTime, tin[MAXN + 3], tout[MAXN + 3];
//LCA variables
int depth[MAXN + 3], P[MAXN + 3][MAXLG + 3];

vector<int> adj[MAXN + 3];

void DFS(int u, int prv) {
    tin[u] = ++dfsTime;

    for (auto v: adj[u]) {
        if (v != prv) {
            depth[v] = depth[u] + 1;
            P[v][0] = u;
            DFS(v, u);
        }
    }

    tout[u] = ++dfsTime;
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
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);

    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
        scanf("%d", &e[i]);

    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfsTime = 0;
    depth[1] = 0;
    memset(P, 0, sizeof(P));
    DFS(1, 0);

    //Init LCA
    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }

    //Init segment tree
    SegmentTree tree = SegmentTree(2 * N);
    for (int i = 1; i <= N; i++) {
        tree.update(tin[i], e[i]);
        tree.update(tout[i], e[i]);
    }

    for (int i = 1; i <= Q; i++) {
        int t;
        scanf("%d", &t);

        if (t == 1) {
            int idx, val;
            scanf("%d%d", &idx, &val);
            tree.update(tin[idx], val);
            tree.update(tout[idx], val);
        } else {
            int u, v, lca;
            scanf("%d%d", &u, &v);

            lca = getLCA(u, v);
            if (lca == u) {
                printf("%d\n", tree.query(tin[lca], tin[v]));
            } else if (lca == v) {
                printf("%d\n", tree.query(tin[lca], tin[u]));
            } else {
                int answer = tree.query(tin[lca], tin[u])^tree.query(tin[lca], tin[v])^tree.query(tin[lca], tin[lca]);
                printf("%d\n", answer);
            }
        }
    }
}
