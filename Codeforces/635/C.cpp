#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
Observation: Build industry city on the leaves first.
Observation: When we build industry city in city u, our answer increases by depth[u] - sz[u] + 1. The reason is because all nodes below this subtree will have one less tourism city.
*/

int n, k, depth[MAXN + 3], sz[MAXN + 3];
vector<int> adj[MAXN + 3], inc;

void DFS(int u, int prv) {
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v != prv) {
            depth[v] = depth[u] + 1;
            DFS(v, u);
            sz[u] += sz[v];
        }
    }

    inc.push_back(depth[u] - sz[u] + 1);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth[1] = 0;
    DFS(1, 1);

    sort(inc.begin(), inc.end(), greater<int>());

    long long int answer = 0;
    for (int i = 0; i < k; i++)
        answer += inc[i];

    printf("%lld\n", answer);
}
