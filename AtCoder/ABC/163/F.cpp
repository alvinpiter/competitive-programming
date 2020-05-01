#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000
#define DEBUG true

/*
sz[u] -> Size of subtree rooted at node u
cnt[c] -> Number of nodes below a subtree rooted at node with color c
sum[c] -> Number of paths which doesn't go through a node with color c
*/

int N, c[MAXN + 3], cnt[MAXN + 3], sz[MAXN + 3];
LL sum[MAXN + 3];
vector<int> adj[MAXN + 3];

LL numWays(int n) {
    return ((LL) n * n + n)/2;
}

void DFS(int u, int prv) {
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v == prv) continue;

        int prvCnt = cnt[c[u]];

        DFS(v, u);

        int cntOther = sz[v] - (cnt[c[u]] - prvCnt); //Number of nodes below u whose color is not c[u].

        sum[c[u]] += numWays(cntOther);
        cnt[c[u]] += cntOther;

        sz[u] += sz[v];
    }

    cnt[c[u]] += 1;
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> c[i];

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(sz, 0, sizeof(sz));
    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));

    DFS(1, 1);

    for (int c = 1; c <= N; c++) {
        LL all = numWays(N);

        //Using DFS above, we only count number of paths below a node. We also need to count number of path above it.
        LL aboveCnt = (sz[1] - cnt[c]);

        cout << all - (sum[c] + numWays(aboveCnt)) << endl;
    }
}
