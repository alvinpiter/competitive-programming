#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int parent[MAXN + 3], sz[MAXN + 3];

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}

void joinSet(int u, int v) {
    if (isSameSet(u, v))
        return;
    else {
        int pu = findSet(u);
        int pv = findSet(v);
        parent[pu] = pv;
        sz[pv] += sz[pu];
    }
}

int N, M, closedBarn[MAXN + 3], numOpen;
vector<int> adj[MAXN + 3];
bool isOpen[MAXN + 3], answer[MAXN + 3];

int main() {
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= N; i++)
        scanf("%d", &closedBarn[i]);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    memset(isOpen, false, sizeof(isOpen));

    for (int i = N; i >= 1; i--) {
        int u = closedBarn[i];

        isOpen[u] = true;
        numOpen += 1;
        for (auto v: adj[u]) {
            if (isOpen[v])
                joinSet(u, v);
        }

        answer[i] = (sz[findSet(u)] == numOpen);
    }

    for (int i = 1; i <= N; i++) {
        if (answer[i])
            printf("YES\n");
        else
            printf("NO\n");
    }
}
