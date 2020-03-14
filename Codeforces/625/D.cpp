#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
dist[i] = distance from p[K] to i via reversed edges
*/
int N, M, K, p[MAXN + 3], dist[MAXN + 3], mini, maxi;
vector<int> adj[MAXN + 3], adjRev[MAXN + 3];

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adjRev[v].push_back(u);
    }

    scanf("%d", &K);
    for (int i = 1; i <= K; i++)
        scanf("%d", &p[i]);

    for (int i = 1; i <= N; i++)
        dist[i] = MAXN;

    queue<int> Q;
    dist[p[K]] = 0;
    Q.push(p[K]);

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();

        for (auto v: adjRev[u]) {
            if (dist[v] == MAXN) {
                dist[v] = dist[u] + 1;
                Q.push(v);
            }
        }
    }

    mini = maxi = 0;
    for (int i = 1; i <= K - 1; i++) {
        //Is there a shortest path from p[i] to p[K] that goes through edge p[i]-p[i + 1]?
        if (dist[p[i]] != dist[p[i + 1]] + 1)
            mini += 1;

        //Is there a shortest path from p[i] to p[K] that doesn't go through edge p[i]-p[i + 1]?
        bool exist = false;
        for (int v: adj[p[i]]) {
            if (v != p[i + 1] && dist[p[i]] == dist[v] + 1) {
                exist = true;
                break;
            }
        }

        if (exist)
            maxi += 1;
    }

    printf("%d %d\n", mini, maxi);
}
