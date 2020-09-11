#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e10
#define MAXN 250

/*
Observation: Putting haybale at the edge that doesn't belong to shortest path is useless.
There are only O(N) edges that belongs to shortest path.
*/

int N, M, weight[MAXN + 3][MAXN + 3], prv[MAXN + 3];
LL dist[MAXN + 3];
vector<int> adj[MAXN + 3];

void Dijkstra() {
    for (int i = 1; i <= N; i++) {
        prv[i] = -1;
        dist[i] = INF;
    }

    dist[1] = 0;
    priority_queue<pair<LL, int> > pq;
    pq.push({-dist[1], 1});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int u = top.second;

        for (auto v: adj[u]) {
            if (dist[v] > dist[u] + weight[u][v]) {
                prv[v] = u;
                dist[v] = dist[u] + weight[u][v];
                pq.push({-dist[v], v});
            }
        }
    }
}

int main() {
    freopen("rblock.in", "r", stdin);
    freopen("rblock.out", "w", stdout);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back(v);
        adj[v].push_back(u);
        weight[u][v] = weight[v][u] = w;
    }

    Dijkstra();

    LL shortestPathLength = dist[N];

    vector<pair<int, int> > spEdges;
    int current = N;
    while (true) {
        if (prv[current] != -1)
            spEdges.push_back({prv[current], current});
        else
            break;

        current = prv[current];
    }

    LL maxDiff = 0;
    for (auto edge: spEdges) {
        int u = edge.first, v = edge.second;
        weight[u][v] *= 2;
        weight[v][u] *= 2;

        Dijkstra();

        maxDiff = max(maxDiff, dist[N] - shortestPathLength);

        weight[u][v] /= 2;
        weight[v][u] /= 2;
    }

    cout << maxDiff << endl;
}
