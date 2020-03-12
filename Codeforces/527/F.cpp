#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, a[MAXN + 3];
LL sumAllA, sumA[MAXN + 3], costDown[MAXN + 3], costUp[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS1(int u, int prv) {
    sumA[u] = a[u];
    costDown[u] = 0;
    for (auto v: adj[u]) {
        if (v != prv) {
            DFS1(v, u);
            sumA[u] += sumA[v];
            costDown[u] += costDown[v] + sumA[v];
        }
    }
}

void DFS2(int u, int prv) {
    LL prefixSumA = 0;
    LL prefixSumCost = 0;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v == prv) continue;

        costUp[v] += prefixSumCost + 2 * prefixSumA;

        prefixSumCost += costDown[v];
        prefixSumA += sumA[v];
    }

    LL suffixSumA = 0;
    LL suffixSumCost = 0;
    for (int i = adj[u].size() - 1; i >= 0; i--) {
        int v = adj[u][i];

        if (v == prv) continue;

        costUp[v] += suffixSumCost + 2 * suffixSumA;

        suffixSumCost += costDown[v];
        suffixSumA += sumA[v];
    }

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v == prv) continue;

        costUp[v] += costUp[u] + (sumAllA - sumA[u]) + a[u];
        DFS2(v, u);
    }
}

int main() {
    scanf("%d", &n);

    sumAllA = 0;
    for (int i = 1; i <= n; i++) {
         scanf("%d", &a[i]);
         sumAllA += a[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(costDown, 0, sizeof(costDown));
    memset(costUp, 0, sizeof(costUp));

    DFS1(1, 1);
    DFS2(1, 1);

    LL best = 0;
    for (int i = 1; i <= n; i++)
        best = max(best, costDown[i] + costUp[i]);

    printf("%lld\n", best);
}
