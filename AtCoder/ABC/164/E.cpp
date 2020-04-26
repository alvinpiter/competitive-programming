#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e15
#define MAXN 50
#define MAXS 2500

int N, M, S, C[MAXN + 3], D[MAXN + 3];
vector<pair<int, pair<int, int> > > adj[MAXN + 3]; //{v, {a, b}}
LL dist[MAXN + 3][MAXS + 3];

int main() {
    scanf("%d%d%d", &N, &M, &S);
    for (int i = 1; i <= M; i++) {
        int u, v, a, b;
        scanf("%d%d%d%d", &u, &v, &a, &b);

        adj[u].push_back({v, {a, b}});
        adj[v].push_back({u, {a, b}});
    }

    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &C[i], &D[i]);
    }

    S = min(S, MAXS);

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= MAXS; j++) {
            dist[i][j] = INF;
        }
    }

    priority_queue<pair<LL, pair<int, int> > > pq; //{dist, {currentNode, currentSilver}}

    dist[1][S] = 0;
    pq.push({-dist[1][S], {1, S}});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();

        int node = top.second.first;
        int silver = top.second.second;

        //try exchanging gold
        if (true) {
            int cost = D[node];
            int nextSilver = min(MAXS, silver + C[node]);
            if (dist[node][nextSilver] > dist[node][silver] + cost) {
                dist[node][nextSilver] = dist[node][silver] + cost;
                pq.push({-dist[node][nextSilver], {node, nextSilver}});
            }
        }

        //try going to neighboring nodes
        for (int i = 0; i < adj[node].size(); i++) {
            int nextNode = adj[node][i].first;
            int neededSilver = adj[node][i].second.first;
            int cost = adj[node][i].second.second;

            if (neededSilver <= silver && dist[nextNode][silver - neededSilver] > dist[node][silver] + cost) {
                dist[nextNode][silver - neededSilver] = dist[node][silver] + cost;
                pq.push({-dist[nextNode][silver - neededSilver], {nextNode, silver - neededSilver}});
            }
        }
    }

    for (int node = 2; node <= N; node++) {
        LL minDist = INF;
        for (int silver = 0; silver <= MAXS; silver++)
            minDist = min(minDist, dist[node][silver]);

        printf("%lld\n", minDist);
    }
}
