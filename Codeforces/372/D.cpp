#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e15
#define MAXN 1000
#define MAXM 10000

int N, M, L, S, T, cost[MAXN + 3][MAXN + 3], prv[MAXN + 3];
bool isFixedEdge[MAXN + 3][MAXN + 3];
pair<int, int> edges[MAXM + 3];
vector<int> adj[MAXN + 3];
LL dist[MAXN + 3];

LL Dijkstra(bool onlyUseFixedEdges) {
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        prv[i] = -1;
    }

    dist[S] = 0;

    priority_queue<pair<LL, int> > pq;
    pq.push({-dist[S], S});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int u = top.second;

        for (auto v: adj[u]) {
            if (onlyUseFixedEdges && !isFixedEdge[u][v])
                continue;

            if (dist[v] > dist[u] + cost[u][v]) {
                dist[v] = dist[u] + cost[u][v];
                prv[v] = u;

                pq.push({-dist[v], v});
            }
        }
    }

    return dist[T];
}

int main() {
    scanf("%d%d%d%d%d", &N, &M, &L, &S, &T);

    memset(cost, -1, sizeof(cost));
    memset(isFixedEdge, true, sizeof(isFixedEdge));
    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);

        if (c == 0) {
            isFixedEdge[u][v] = isFixedEdge[v][u] = false;
            c = 1;
        }

        edges[i] = {u, v};
        cost[u][v] = cost[v][u] = c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    LL sp;

    //Only use fixed edges
    sp = Dijkstra(true);
    if (sp < L) {
        printf("NO\n");
        return 0;
    }

    //All variable edges' weight is set to 1
    sp = Dijkstra(false);
    if (sp > L) {
        printf("NO\n");
        return 0;
    }

    //Up until now, all shortest path is <= L and goes through at least 1 variable edges

    //This loop at most runs m times
    while (true) {
        sp = Dijkstra(false);
        if (sp == L)
            break;

        int current = T;
        while (prv[current] != -1) {
            if (!isFixedEdge[prv[current]][current]) {
                cost[prv[current]][current] += (L - sp);
                cost[current][prv[current]] += (L - sp);
                break;
            }

            current = prv[current];
        }
    }

    printf("YES\n");
    for (int i = 0; i < M; i++) {
        printf("%d %d %d\n", edges[i].first, edges[i].second, cost[edges[i].first][edges[i].second]);
    }
}
