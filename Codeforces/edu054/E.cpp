#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000

/*
Maintain something like prefix sum during DFS.
*/

int n, m;
vector<int> adj[MAXN + 3];
vector<pair<int, int> > queries[MAXN + 3]; //{d, x}
LL updates[MAXN + 3], answer[MAXN + 3];

void DFS(int u, int prv, int depth, LL cumulativeSum) {
    //apply all queries
    for (auto q: queries[u]) {
        int d = q.first;
        int x = q.second;

        updates[depth] += x;
        if (depth + d + 1 < n)
            updates[depth + d + 1] -= x;
    }

    cumulativeSum += updates[depth];
    answer[u] = cumulativeSum;

    for (auto v: adj[u]) {
        if (v != prv)
            DFS(v, u, depth + 1, cumulativeSum);
    }

    //un-apply all queries
    for (auto q: queries[u]) {
        int d = q.first;
        int x = q.second;

        updates[depth] -= x;
        if (depth + d + 1 < n)
            updates[depth + d + 1] += x;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int v, d, x;
        scanf("%d%d%d", &v, &d, &x);

        queries[v].push_back({d, x});
    }

    memset(updates, 0, sizeof(updates));
    DFS(1, 1, 1, 0);

    for (int i = 1; i <= n; i++)
        printf("%lld ", answer[i]);
    printf("\n");
}
