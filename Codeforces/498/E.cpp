#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, q, tin[MAXN + 3], tout[MAXN + 3], dfsTime, who[MAXN + 3];
vector<int> children[MAXN + 3];

void DFS(int u) {
    dfsTime += 1;
    tin[u] = dfsTime;
    who[tin[u]] = u;

    sort(children[u].begin(), children[u].end());
    for (auto v: children[u])
        DFS(v);

    tout[u] = dfsTime;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);

        children[p].push_back(i);
    }

    dfsTime = 0;
    DFS(1);

    for (int i = 1; i <= q; i++) {
        int u, k;
        scanf("%d%d", &u, &k);

        int t = tin[u] + k - 1;

        if (t > tout[u]) {
            printf("-1\n");
        } else {
            printf("%d\n", who[t]);
        }
    }
}
