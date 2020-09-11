#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, deg[MAXN + 3], cntLeaves;

int main() {
    scanf("%d", &n);

    memset(deg, 0, sizeof(deg));
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        deg[u] += 1;
        deg[v] += 1;
    }

    cntLeaves = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1)
            cntLeaves += 1;
    }

    printf("%d\n", (cntLeaves + 1)/2);
}
