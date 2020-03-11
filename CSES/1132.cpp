#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, distDown[MAXN + 3], distUp[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS1(int u, int prv) {
    distDown[u] = 0;
    for (auto v: adj[u]) {
        if (v != prv) {
            DFS1(v, u);
            distDown[u] = max(distDown[u], 1 + distDown[v]);
        }
    }
}

void DFS2(int u, int prv) {
    int prefixMax = -MAXN;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v == prv) continue;

        distUp[v] = max(distUp[v], prefixMax + 2);
        prefixMax = max(prefixMax, distDown[v]);
    }

    int suffixMax = -MAXN;
    for (int i = adj[u].size() - 1; i >= 0; i--) {
        int v = adj[u][i];

        if (v == prv) continue;

        distUp[v] = max(distUp[v], suffixMax + 2);
        suffixMax = max(suffixMax, distDown[v]);
    }

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v == prv) continue;

        distUp[v] = max(distUp[v], distUp[u] + 1); //Distance to u

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

    memset(distUp, 0, sizeof(distUp));
    DFS2(1, 1);

    for (int i = 1; i <= N; i++) {
        if (i > 1)
            printf(" ");

        printf("%d", max(distDown[i], distUp[i]));
    }
    printf("\n");
}
