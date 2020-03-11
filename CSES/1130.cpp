#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, dp[MAXN + 3][2];
vector<int> adj[MAXN + 3], children[MAXN + 3];

void DFS(int u, int prv) {
    for (auto v: adj[u]) {
        if (v != prv) {
            children[u].push_back(v);
            DFS(v, u);
        }
    }
}

int solve(int u, int taken) {
    if (dp[u][taken] != -1)
        return dp[u][taken];

    if (taken == 1) {
        int result = 0;
        for (auto v: children[u])
            result += solve(v, 0);

        return dp[u][taken] = result;
    } else {
        int allSum = 0;
        int result = 0;
        int nChildren = children[u].size();

        allSum = 0;
        for (int i = 0; i < nChildren; i++) {
            int v = children[u][i];
            allSum += solve(v, 0);
        }

        result = allSum;

        for (int i = 0; i < nChildren; i++) {
            int v = children[u][i];
            result = max(result, 1 + solve(v, 1) + (allSum - solve(v, 0)));
        }

        return dp[u][taken] = result;
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1, 1);

    memset(dp, -1, sizeof(dp));

    printf("%d\n", solve(1, 0));
}
