#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000
#define MAXM 500000

int t, n, m, a, b, u[MAXM + 3], v[MAXM + 3], parent[MAXN + 3], sz[MAXN + 3];

int findSet(int x) {
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool isSameSet(int x, int y) {
    return (findSet(x) == findSet(y));
}

void joinSet(int x, int y) {
    if (isSameSet(x, y)) return;

    int px = findSet(x);
    int py = findSet(y);
    parent[px] = py;
    sz[py] += sz[px];
}

void resetParentAndSize(int N) {
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d%d%d", &n, &m, &a, &b);

        for (int i = 1; i <= m; i++) {
            scanf("%d%d", &u[i], &v[i]);
        }

        resetParentAndSize(n);

        //ignore a
        for (int i = 1; i <= m; i++) {
            if (u[i] == a || v[i] == a) continue;
            joinSet(u[i], v[i]);
        }

        int cnt1 = n - sz[findSet(b)] - 1; //how many nodes that are not in the same cluster with b

        resetParentAndSize(n);

        //ignore b
        for (int i = 1; i <= m; i++) {
            if (u[i] == b || v[i] == b) continue;
            joinSet(u[i], v[i]);
        }

        int cnt2 = n - sz[findSet(a)] - 1; // how many nodes that are not in the same cluster with a

        printf("%lld\n", (LL) cnt1 * cnt2);
    }
}
