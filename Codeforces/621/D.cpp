#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
dist[0][i] is distance from node 1 to node i.
dist[1][i] is distance from node n to node i.

When we add a new edge between two special node a and b, the new shortest path might be:
1 + min(dist[0][a] + dist[1][b], dist[1][a] + dist[0][b]). We want to maximize this.

We can sort the special nodes in order of increasing dist[0][special[i]] - dist[1][special[i]].
In this order, we are sure the new shortest path must go from 1-special[i]-special[j]-n, where i < j.
*/

int n, m, k, special[MAXN + 3], dist[2][MAXN + 3];
vector<int> adj[MAXN + 3];

bool cmp(int a, int b) {
    return (dist[0][a] - dist[1][a]) < (dist[0][b] - dist[1][b]);
}

void BFS(int who) {
    int origin = (who == 0 ? 1 : n);

    for (int i = 1; i <= n; i++)
        dist[who][i] = -1;

    dist[who][origin] = 0;

    queue<int> q;
    q.push(origin);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v: adj[u]) {
            if (dist[who][v] == -1) {
                dist[who][v] = dist[who][u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++)
        scanf("%d", &special[i]);

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    BFS(0); //starting point from 1
    BFS(1); //starting point from n

    int shortestPathLength = dist[0][n];
    int newPathLength = 0;

    sort(special + 1, special + k + 1, cmp);

    int suffixMax = dist[1][special[k]];
    for (int i = k - 1; i >= 1; i--) {
        newPathLength = max(newPathLength, dist[0][special[i]] + suffixMax + 1);
        suffixMax = max(suffixMax, dist[1][special[i]]);
    }

    printf("%d\n", min(shortestPathLength, newPathLength));
}
