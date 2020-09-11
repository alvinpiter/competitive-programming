#include<bits/stdc++.h>
using namespace std;
#define INF 2e9

void Dijkstra(vector<vector<pair<int, int> > > adj, int dist[], int source) {
    int N = adj.size();

    for (int i = 0; i < N; i++)
        dist[i] = INF;

    priority_queue<pair<int, int> > pq;
    dist[source] = 0;
    pq.push({-dist[source], source});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();

        int u = top.second;
        for (auto e: adj[u]) {
            int v = e.first, cost = e.second;
            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                pq.push({-dist[v], v});
            }
        }
    }
}

int main() {
    freopen("gpsduel.in", "r", stdin);
    freopen("gpsduel.out", "w", stdout);

    int N, M;

    cin >> N >> M;

    vector<vector<pair<int, int> > > adj1(N), adj2(N), revAdj1(N), revAdj2(N);
    for (int i = 0; i < M; i++) {
        int u, v, w1, w2;
        cin >> u >> v >> w1 >> w2;

        u -= 1;
        v -= 1;

        adj1[u].push_back({v, w1});
        revAdj1[v].push_back({u, w1});

        adj2[u].push_back({v, w2});
        revAdj2[v].push_back({u, w2});
    }

    //dist1N -> shortest path from N using adj1
    int dist1N[N + 3];
    Dijkstra(revAdj1, dist1N, N - 1);

    int dist2N[N + 3];
    Dijkstra(revAdj2, dist2N, N - 1);

    vector<vector<pair<int, int> > > adj3(N);
    for (int u = 0; u < N; u++) {
        for (int i = 0; i < adj1[u].size(); i++) {
            int v = adj1[u][i].first;
            int w1 = adj1[u][i].second, w2 = adj2[u][i].second;

            int w3 = 2;
            if (dist1N[u] == dist1N[v] + w1)
                w3 -= 1;

            if (dist2N[u] == dist2N[v] + w2)
                w3 -= 1;

            adj3[u].push_back({v, w3});
        }
    }

    int dist31[N + 3];
    Dijkstra(adj3, dist31, 0);

    cout << dist31[N - 1] << endl;
}
