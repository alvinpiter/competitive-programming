#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int N, sz[MAXN + 3];
vector<int> adj[MAXN + 3];
LL totalDown[MAXN + 3], totalUp[MAXN + 3];

void DFS1(int u, int prv) {
    sz[u] = 1;
    totalDown[u] = 0;
    for (auto v: adj[u]) {
        if (v != prv) {
            DFS1(v, u);

            sz[u] += sz[v];
            totalDown[u] += totalDown[v] + sz[v];
        }
    }
}

void DFS2(int u, int prv) {
    LL prefixTotal = 0;
    int prefixSz = 0;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v == prv) continue;

        totalUp[v] += prefixTotal + 2 * prefixSz;

        prefixTotal += totalDown[v];
        prefixSz += sz[v];
    }

    LL suffixTotal = 0;
    int suffixSz = 0;
    for (int i = adj[u].size() - 1; i >= 0; i--) {
        int v = adj[u][i];

        if (v == prv) continue;

        totalUp[v] += suffixTotal + 2 * suffixSz;

        suffixTotal += totalDown[v];
        suffixSz += sz[v];
    }

    for (auto v: adj[u]) {
        if (v == prv) continue;

        totalUp[v] += totalUp[u] + (N - sz[u]) + 1; //1 is for u itself.

        DFS2(v, u);
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS1(1, 1);

    memset(totalUp, 0, sizeof(totalUp));
    DFS2(1, 1);

    for (int i = 1; i <= N; i++) {
        if (i > 1)
            printf(" ");

        printf("%lld", totalDown[i] + totalUp[i]);
    }
    printf("\n");
}
