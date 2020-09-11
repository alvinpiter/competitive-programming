#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define DEBUG false

/*
distDown[i] = largest distance from i to j, where j is a marked node and j is in subtree rooted at i.
distUp[i] = largest distance from i to j, where j is a marked node and j is not in subtree rooted at i.
dist[i] = max(distDown[i], distUp[i])
*/

int T, N, M, distDown[MAXN + 3], distUp[MAXN + 3], dist[MAXN + 3];
bool marked[MAXN + 3];
vector<int> adj[MAXN + 3];

void reset() {
    for (int i = 1; i <= MAXN; i++) {
        adj[i].clear();
        distDown[i] = -MAXN;
        distUp[i] = -MAXN;
        marked[i] = false;
    }
}

//Fill distDown[]
void DFS1(int u, int prev) {
    if (marked[u])
        distDown[u] = 0;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != prev) {
            DFS1(v, u);
            distDown[u] = max(distDown[u], 1 + distDown[v]);
        }
    }
}

//Fill distUp[]
void DFS2(int u, int prev) {
    int largestPrefix = -MAXN;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v != prev) {
            distUp[v] = max(distUp[v], max(largestPrefix, distUp[u] + 1));

            if (marked[u])
                distUp[v] = max(distUp[v], 1);

            largestPrefix = max(largestPrefix, distDown[v] + 2);
        }
    }

    int largestSuffix = -MAXN;
    for (int i = adj[u].size() - 1; i >= 0; i--) {
        int v = adj[u][i];

        if (v != prev) {
            distUp[v] = max(distUp[v], max(largestSuffix, distUp[u] + 1));

            if (marked[u])
                distUp[v] = max(distUp[v], 1);

            largestSuffix = max(largestSuffix, distDown[v] + 2);
        }
    }

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != prev)
            DFS2(v, u);
    }
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        reset();

        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= M; i++) {
            int m;
            scanf("%d", &m);

            marked[m] = true;
        }

        DFS1(1, 1);
        DFS2(1, 1);

        int bestNode = 1;
        for (int i = 1; i <= N; i++) {
            dist[i] = max(distDown[i], distUp[i]);
            if (dist[i] < dist[bestNode])
                bestNode = i;
        }

        printf("Case #%d: %d %d\n", cases, bestNode, dist[bestNode]);
    }
}
