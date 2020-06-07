#include<bits/stdc++.h>
using namespace std;
#define MAXN 50000
#define INF 1000000000

/*
Run Dijkstra's algorithm twice:
* First is ordinary Dijkstra to calculate shortest path from N to any vertex
* Second is Dijkstra with state {vertex, hasSeenHaybale}, i.e the shortest distance
  to visit vertex where we have seen a haybale along the way. There are two kinds or transition:
  - Ordinary transition (value of hasSeenHaybale does not change)
  - Visit a haybale (hasSeenHaybale must be 0 currently). When we see a haybale, the distance of the
    next state will be decreased by the haybale's yumminess.

Finally, compare dist[vertex][hasSeenHaybale] and dist[vertex].
*/

int N, M, K, dist1[MAXN + 3], dist2[MAXN + 3][2], yumminess[MAXN + 3];
bool isYummy[MAXN + 3];
vector<pair<int, int> > adj[MAXN + 3];

int main() {
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);

    scanf("%d%d%d", &N, &M, &K);
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    memset(isYummy, false, sizeof(isYummy));
    memset(yumminess, 0, sizeof(yumminess));
    for (int i = 1; i <= K; i++) {
        int idx, yum;
        scanf("%d%d", &idx, &yum);
        isYummy[idx] = true;
        yumminess[idx] = max(yumminess[idx], yum);
    }

    for (int i = 1; i <= N; i++)
        dist1[i] = INF;

    priority_queue<pair<int, int> > pq1;
    dist1[N] = 0;
    pq1.push({-dist1[N], N});

    while (!pq1.empty()) {
        auto top = pq1.top(); pq1.pop();
        int u = top.second;

        for (auto e: adj[u]) {
            int v = e.first;
            int cost = e.second;
            if (dist1[v] > dist1[u] + cost) {
                dist1[v] = dist1[u] + cost;
                pq1.push({-dist1[v], v});
            }
        }
    }

    for (int i = 1; i <= N; i++)
        dist2[i][0] = dist2[i][1] = INF;

    priority_queue<pair<int, pair<int, int> > > pq2;
    dist2[N][0] = 0;
    pq2.push({-dist2[N][0], {N, 0}});

    while (!pq2.empty()) {
        auto top = pq2.top(); pq2.pop();
        int u = top.second.first;
        int seenHaybale = top.second.second;

        for (auto e: adj[u]) {
            int v = e.first;
            int cost = e.second;

            if (dist2[v][seenHaybale] > dist2[u][seenHaybale] + cost) {
                dist2[v][seenHaybale] = dist2[u][seenHaybale] + cost;
                pq2.push({-dist2[v][seenHaybale], {v, seenHaybale}});
            }

            if (seenHaybale == 0 && isYummy[v]) {
                if (dist2[v][1] > dist2[u][0] + cost - yumminess[v]) {
                    dist2[v][1] = dist2[u][0] + cost - yumminess[v];
                    pq2.push({-dist2[v][1], {v, 1}});
                }
            }
        }
    }

    for (int i = 1; i <= N - 1; i++) {
        if (dist2[i][1] <= dist1[i])
            printf("1\n");
        else
            printf("0\n");
    }
}
