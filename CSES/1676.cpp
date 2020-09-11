#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int n, m, parent[MAXN + 3], sz[MAXN + 3], numComponent, maxSize;

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}

void joinSet(int u, int v) {
    if (!isSameSet(u, v)) {
        numComponent -= 1;

        int pu = findSet(u);
        int pv = findSet(v);
        parent[pu] = parent[pv];
        sz[pv] += sz[pu];

        maxSize = max(maxSize, sz[pv]);
    }
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    numComponent = n;
    maxSize = 1;
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        joinSet(u, v);

        printf("%d %d\n", numComponent, maxSize);
    }
}
