#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 1000

/*
If we have fixed flow rate, to maximize the flow rate over cost, we need to find the minimum cost.

Model the graph as weighted graph, where the weight is the cost.
For every possible edge with flow rate f, let's say it connects node a and b:
    * Find shortest path from 1 to a using edges with flow rate >= f
    * Find shortest path from n to b using edges with flow rate >= f
    * Calculate the flow rate over cost, and then update the answer

Complexity is O(MN log M)
*/

struct Edge {
    int to, cost, rate;
    Edge(int _to, int _cost, int _rate): to(_to), cost(_cost), rate(_rate) {}
};

int N, M, dist[2][MAXN + 3];
vector<Edge> adj[MAXN + 3];
double best;

void Dijkstra(int who, int threshold) {
    int origin = (who == 0 ? 1 : N);

    for (int i = 1; i <= N; i++)
        dist[who][i] = INF;

    priority_queue<pair<int, int> > pq;

    dist[who][origin] = 0;
    pq.push({-dist[who][origin], origin});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();

        int u = top.second;
        for (auto e: adj[u]) {
            int v = e.to, cost = e.cost, rate = e.rate;

            if (rate >= threshold && dist[who][v] > dist[who][u] + cost) {
                dist[who][v] = dist[who][u] + cost;
                pq.push({-dist[who][v], v});
            }
        }
    }
}

int main() {
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int a, b, c, f;
        scanf("%d%d%d%d", &a, &b, &c, &f);

        adj[a].push_back(Edge(b, c, f));
        adj[b].push_back(Edge(a, c, f));
    }

    best = 0;

    //Try each edge as the minimal flow rate
    for (int u = 1; u <= N; u++) {
        for (auto e: adj[u]) {
            int v = e.to;
            int cost = e.cost;
            int rate = e.rate;

            Dijkstra(0, rate);
            Dijkstra(1, rate);

            int totalCost = min(dist[0][u] + cost + dist[1][v], dist[0][v] + cost + dist[1][u]);

            if (totalCost < INF) {
                best = max(best, rate/(totalCost * 1.0));
            }
        }
    }

    best *= 1000000;

    printf("%d\n", (int) best);
}
