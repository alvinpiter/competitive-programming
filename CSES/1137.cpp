#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int N, Q, tin[MAXN + 3], tout[MAXN + 3], dfsTime;
LL v[MAXN + 3], BIT[MAXN + 3];
vector<int> adj[MAXN + 3];

void update(int idx, LL val) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

LL query(int idx) {
    LL result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

LL rangeSum(int a, int b) {
    return query(b) - query(a - 1);
}

void DFS(int u, int prv) {
    tin[u] = ++dfsTime;
    for (auto v: adj[u]) {
        if (v != prv)
            DFS(v, u);
    }
    tout[u] = dfsTime;
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
        scanf("%d", &v[i]);

    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfsTime = 0;
    DFS(1, 1);

    memset(BIT, 0, sizeof(BIT));
    for (int i = 1; i <= N; i++)
        update(tin[i], v[i]);

    for (int i = 1; i <= Q; i++) {
        int t, idx, val;

        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &idx, &val);

            update(tin[idx], (LL) val - v[idx]);
            v[idx] = val;
        } else {
            scanf("%d", &idx);
            printf("%lld\n", rangeSum(tin[idx], tout[idx]));
        }
    }
}
