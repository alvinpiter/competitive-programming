#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXLG 17

/*
Distance between two nodes u and v can be formulated as: dist(u) + dist(v) - 2 * dist(lca(u, v)), where dist(u) is the distance from root to u.

Let's say we want to change the length of edge whose color is c to x.
How does it affect dist(u)?

dist'(u) = dist(u) - sumColor(c, u) + x*numColor(c, u).

sumColor(c, u) is sum of length of edges with color c from root to u.
numColor(c, u) is number of edges with color c from root to u.

How to compute sumColor(c, u)?

For each color, we maintain the lengths in DFS order:
* Whenever we enter a node, we add a pair {dfsTime, length} to the vector.
* Whenever we exit a node, we add a pair {dfsTime, -length} to the vector.

To compute sumColor(c, u), we will need to find the location of u in color c's vector (can be done with binary search).
And then sum all lengths up to this position (can be done with prefix sum).
Keep in mind that whenever we enter or exit a node, we increase the dfsTime.

Similar trick is used to compute numColor(x, u).
*/

//General variables
int N, Q, dist[MAXN + 3];
vector<pair<int, pair<int, int> > > adj[MAXN + 3]; //{neighbor, {color, length}}

//LCA variables
int P[MAXN + 3][MAXLG + 3], depth[MAXN + 3];

//DFS variables
int dfsTime, tin[MAXN + 3], tout[MAXN + 3];
vector<int> dfsTimeOfColor[MAXN + 3];
vector<int> sumLengthOfColor[MAXN + 3]; //ordered by dfsTime
vector<int> sumPresenceOfColor[MAXN + 3]; //ordered by dfsTime

void DFS(int u, int prv, int prvColor, int prvLength) {
    tin[u] = ++dfsTime;

    if (prv != 0) {
        dfsTimeOfColor[prvColor].push_back(tin[u]);
        sumLengthOfColor[prvColor].push_back(prvLength);
        sumPresenceOfColor[prvColor].push_back(1);
    }

    for (auto nxt: adj[u]) {
        int v = nxt.first;
        int c = nxt.second.first;
        int d = nxt.second.second;

        if (v != prv) {
            depth[v] = depth[u] + 1;
            dist[v] = dist[u] + d;
            P[v][0] = u;

            DFS(v, u, c, d);
        }
    }

    tout[u] = ++dfsTime;

    if (prv != 0) {
        dfsTimeOfColor[prvColor].push_back(tout[u]);
        sumLengthOfColor[prvColor].push_back(-prvLength);
        sumPresenceOfColor[prvColor].push_back(-1);
    }
}

void initializePrefixSums() {
    for (int c = 1; c <= N; c++) {
        int sz = (int) dfsTimeOfColor[c].size();
        for (int i = 1; i < sz; i++) {
            sumLengthOfColor[c][i] += sumLengthOfColor[c][i - 1];
            sumPresenceOfColor[c][i] += sumPresenceOfColor[c][i - 1];
        }
    }
}

void initializeLCA() {
    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int u = 1; u <= N; u++) {
            P[u][lg] = P[P[u][lg - 1]][lg - 1];
        }
    }
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

//where u is in dfsTimeOfColor[c]
int indexOfDfsTime(int c, int u) {
    int lo = 0, hi = (int) dfsTimeOfColor[c].size() - 1, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (dfsTimeOfColor[c][mid] < tin[u])
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    if (lo == (int) dfsTimeOfColor[c].size())
        return -1;

    if (dfsTimeOfColor[c][lo] > tin[u])
        return lo - 1;
    else
        return lo;
}

int sumColor(int c, int u) {
    int idx = indexOfDfsTime(c, u);

    if (idx == -1)
        return 0;
    else
        return sumLengthOfColor[c][idx];
}

int numColor(int c, int u) {
    int idx = indexOfDfsTime(c, u);

    if (idx == -1)
        return 0;
    else
        return sumPresenceOfColor[c][idx];
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i < N; i++) {
        int u, v, c, d;
        scanf("%d%d%d%d", &u, &v, &c, &d);

        adj[u].push_back({v, {c, d}});
        adj[v].push_back({u, {c, d}});
    }

    memset(P, 0, sizeof(P));

    dfsTime = 0;
    depth[1] = 0;
    dist[1] = 0;
    DFS(1, 0, 0, 0);

    initializeLCA();
    initializePrefixSums();

    for (int i = 1; i <= Q; i++) {
        int c, x, u, v;
        scanf("%d%d%d%d", &c, &x, &u, &v);

        int lca = getLCA(u, v);

        int uRoot = dist[u] - sumColor(c, u) + x * numColor(c, u);
        int vRoot = dist[v] - sumColor(c, v) + x * numColor(c, v);
        int lcaRoot = dist[lca] - sumColor(c, lca) + x * numColor(c, lca);

        printf("%d\n", uRoot + vRoot - 2 * lcaRoot);
    }
}
