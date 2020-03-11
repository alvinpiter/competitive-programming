#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

/*
who[i] -> Which node has tin equals to i
To support range update and range sum, use difference array technique.

Suppose the value in our array is a1, a2, a3, .., an. Create a BIT with elements:
a1, a2 - a1, a3 - a2, ..., an - an_1

* Element at index i is the prefix sum of difference array.
* When updating element at index i to j by x, update BIT at i (by x) and update BIT at j + 1 (by -x)
*/
int N, Q, tin[MAXN + 3], tout[MAXN + 3], who[MAXN + 3], dfsTime;
LL val[MAXN + 3], pathSum[MAXN + 3], BIT[MAXN + 3];
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

void DFS(int u, int prv) {
    tin[u] = ++dfsTime;
    who[dfsTime] = u;
    for (auto v: adj[u]) {
        if (v != prv) {
            pathSum[v] = pathSum[u] + val[v];
            DFS(v, u);
        }
    }
    tout[u] = dfsTime;
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
        scanf("%d", &val[i]);

    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfsTime = 0;
    pathSum[1] = val[1];
    DFS(1, 1);

    //Construct diff array
    memset(BIT, 0, sizeof(BIT));
    for (int t = 1; t <= N; t++) {
        if (t == 1)
            update(t, pathSum[who[t]]);
        else
            update(t, pathSum[who[t]] - pathSum[who[t - 1]]);
    }

    for (int i = 1; i <= Q; i++) {
        int t, idx, newVal;

        scanf("%d", &t);
        if (t == 1) {
            scanf("%d%d", &idx, &newVal);

            LL diff = (LL) newVal - val[idx];
            update(tin[idx], diff);
            update(tout[idx] + 1, -diff);

            val[idx] = newVal;
        } else {
            scanf("%d", &idx);
            printf("%lld\n", query(tin[idx]));
        }
    }
}
