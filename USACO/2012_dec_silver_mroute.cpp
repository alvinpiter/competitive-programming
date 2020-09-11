#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 500

struct Pipe {
    int to, lat, cap;
    Pipe(int _to, int _lat, int _cap): to(_to), lat(_lat), cap(_cap) {}
};

int N, M, X, dist[MAXN + 3];
vector<Pipe> adj[MAXN + 3];
vector<int> capacities;

void Dijkstra(int dist[], int source, int minCap) {
    for (int i = 1; i <= N; i++)
        dist[i] = INF;

    priority_queue<pair<int, int> > pq;
    dist[source] = 0;
    pq.push({-dist[source], source});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int u = top.second;

        for (auto p: adj[u]) {
            int v = p.to, lat = p.lat, cap = p.cap;

            if (cap >= minCap && dist[v] > dist[u] + lat) {
                dist[v] = dist[u] + lat;
                pq.push({-dist[v], v});
            }
        }
    }
}

int main() {
    freopen("mroute.in", "r", stdin);
    freopen("mroute.out", "w", stdout);

    cin >> N >> M >> X;
    for (int i = 1; i <= M; i++) {
        int u, v, l, c;
        cin >> u >> v >> l >> c;

        capacities.push_back(c);
        adj[u].push_back(Pipe(v, l, c));
        adj[v].push_back(Pipe(u, l, c));
    }

    double answer = 1e9;
    for (int u = 1; u <= N; u++) {
        for (auto p: adj[u]) {
            int v = p.to, lat = p.lat, cap = p.cap;

            int dist1[MAXN + 3];
            Dijkstra(dist1, 1, cap);

            int distN[MAXN + 3];
            Dijkstra(distN, N, cap);

            int totalLat = dist1[u] + distN[v] + lat;
            if (totalLat < INF)
                answer = min(answer, totalLat + X/(cap * 1.0));
        }
    }

    printf("%.0lf\n", floor(answer));
}
