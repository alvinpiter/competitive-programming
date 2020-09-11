#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 1000

//Number of days of travel is at most 1000, because if it is more than 1000 the cost will be too high.

int N, M, C, money[MAXN + 3];
int dp[MAXN + 3][MAXN + 3];
vector<int> adj[MAXN + 3];

//maximum money reachable where currently at city u and has d days to travel. must end up at city 1.
int solve(int u, int d) {
    if (d == 0)
        return (u == 1 ? 0 : -INF);

    if (dp[u][d] != -1)
        return dp[u][d];

    int best = -INF;
    for (auto v: adj[u]) {
        best = max(best, solve(v, d - 1) + money[u]);
    }

    return dp[u][d] = best;
}

int main() {
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);

    scanf("%d%d%d", &N, &M, &C);
    for (int i = 1; i <= N; i++)
        scanf("%d", &money[i]);

    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }

    memset(dp, -1, sizeof(dp));

    int best = 0;
    for (int d = 1; d <= 1000; d++) {
        best = max(best, solve(1, d) - C*d*d);
    }

    printf("%d\n", best);
}
