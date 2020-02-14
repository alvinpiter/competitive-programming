#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100000
#define MAXLG 17
#define ROOT 1
#define BLACK 0
#define WHITE 1

set<int> adj[MAXN + 3]; //Store the adjacency list using set to ease edge removal
int N, Q, color[MAXN + 3];

//Variables for LCA
int parent[MAXN + 3][MAXLG + 3], depth[MAXN + 3];

//Variables for centroid decomposition
int rootSize, centroidParent[MAXN + 3], sz[MAXN + 3];

//Variables for answering queries
multiset<int> minDist[MAXN + 3];

//##################################################################
//LCA
//##################################################################
void initDepth(int u, int prev) {
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = *it;

        if (v != prev) {
            depth[v] = depth[u] + 1;
            parent[v][0] = u;
            initDepth(v, u);
        }
    }
}

void initParent() {
    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            parent[i][lg] = parent[parent[i][lg - 1]][lg - 1];
        }
    }
}

void preprocessLCA() {
    depth[ROOT] = 0;
    parent[ROOT][0] = 0;

    initDepth(1, 0);
    initParent();
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for (int i = 0; i <= MAXLG; i++) {
        if (diff & (1 << i))
            v = parent[v][i];
    }

    if (u == v)
        return u;

    for (int i = MAXLG; i >= 0; i--) {
        if (parent[u][i] != -1 && parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    return parent[u][0];
}

int dist(int u, int v) {
    int lca = getLCA(u, v);
    return depth[u] + depth[v] - 2 * depth[lca];
}

//##################################################################
//Centroid decomposition
//##################################################################
void initSize(int u, int prev) {
    sz[u] = 1;
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = *it;
        if (v != prev) {
            initSize(v, u);
            sz[u] += sz[v];
        }
    }
}

int getCentroid(int u, int prev) {
    int centroid = u;
    for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = *it;
        if (v != prev && sz[v] > rootSize/2)
            centroid = getCentroid(v, u);
    }

    return centroid;
}

void decompose(int u, int prev) {
    initSize(u, prev);
    rootSize = sz[u];

    int centroid = getCentroid(u, prev);

    centroidParent[centroid] = prev;
    for (auto it = adj[centroid].begin(); it != adj[centroid].end(); ++it) {
        int v = *it;

        adj[v].erase(centroid);
        decompose(v, centroid);
    }
}

//##################################################################
//Answer queries
//##################################################################
void update(int u, bool paintToWhite) {
    int current = u;
    while (current != 0) {
        if (paintToWhite) {
            minDist[current].insert(dist(u, current));
        } else {
            minDist[current].erase(minDist[current].find(dist(u, current)));
        }

        current = centroidParent[current];
    }
}

int query(int u) {
    int current = u;
    int result = INF;
    while (current != 0) {
        if (!minDist[current].empty())
            result = min(result, dist(u, current) + *minDist[current].begin());

        current = centroidParent[current];
    }

    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        color[i] = BLACK;

    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].insert(v);
        adj[v].insert(u);
    }

    preprocessLCA();
    decompose(ROOT, 0);

    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        int type, v;
        scanf("%d%d", &type, &v);

        if (type == 0) {
            update(v, color[v] == BLACK);
            color[v] = (color[v] == BLACK ? WHITE : BLACK);
        } else {
            int result = query(v);
            if (result < INF)
                printf("%d\n", result);
            else
                printf("-1\n");
        }
    }
}
