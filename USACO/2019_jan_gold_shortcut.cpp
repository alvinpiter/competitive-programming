#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 2000000000
#define MAXN 10000

/*
* Run Dijkstra's algorithm from the barn (vertex 1).
* From each vertex i, we would like to know where the cows will go from here.
  Then we will discard all edges that will not be traversed by cows. The left over edges
  will be a tree.
* When we add a shortcut to vertex i, the reduction will be subtreeSize[i] * (dist[i] - T)
*/

int N, M, T, c[MAXN + 3], dist[MAXN + 3];
vector<pair<int, int> > adj[MAXN + 3];
vector<int> treeAdj[MAXN + 3];
int subtreeSize[MAXN + 3];

void DFS(int u, int prv) {
    subtreeSize[u] = c[u];
    for (auto v: treeAdj[u]) {
        if (v != prv) {
            DFS(v, u);
            subtreeSize[u] += subtreeSize[v];
        }
    }
}

int main() {
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);

    scanf("%d%d%d", &N, &M, &T);
    for (int i = 1; i <= N; i++)
        scanf("%d", &c[i]);

    for (int i = 1; i <= M; i++) {
        int u, v, cost;
        scanf("%d%d%d", &u, &v, &cost);

        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }

    //Dijkstra's
    for (int i = 1; i <= N; i++)
        dist[i] = INF;

    priority_queue<pair<int, int> > pq;
    dist[1] = 0;
    pq.push({-dist[1], 1});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int u = top.second;

        for (auto e: adj[u]) {
            int v = e.first;
            int cost = e.second;

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pq.push({-dist[v], v});
            }
        }
    }

    //From each vertex, find out where the cow will go
    for (int u = 1; u <= N; u++) {
        int to = INF;
        for (auto e: adj[u]) {
            int v = e.first;
            int cost = e.second;

            if (dist[v] + cost == dist[u])
                to = min(to, v);
        }

        if (to < INF) {
            //cow at vertex u will got to vertex to
            treeAdj[u].push_back(to);
            treeAdj[to].push_back(u);
        }
    }

    //Find size of each subtree
    memset(subtreeSize, 0, sizeof(subtreeSize));
    DFS(1, 0);

    //Find best shortcut
    LL maxReduction = 0;
    for (int i = 2; i <= N; i++) {
        maxReduction = max(maxReduction, (LL) subtreeSize[i] * (dist[i] - T));
    }

    printf("%lld\n", maxReduction);
}
