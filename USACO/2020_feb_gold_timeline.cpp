#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
Define minStartTime(x) as minimum possible start time for event x. The formula is:
max(Sx, max(minStartTime(y) + gap)), where y is event which preceeds x.
*/

int N, M, C, S[MAXN + 3], dp[MAXN + 3];
vector<pair<int, int> > prv[MAXN + 3];

int minStartTime(int u) {
    if (dp[u] != -1)
        return dp[u];

    int result = S[u];
    for (auto p: prv[u]) {
        int v = p.first;
        int gap = p.second;
        result = max(result, minStartTime(v) + gap);
    }

    return dp[u] = result;
}

int main() {
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);

    scanf("%d%d%d", &N, &M, &C);
    for (int i = 1; i <= N; i++)
        scanf("%d", &S[i]);

    for (int i = 1; i <= C; i++) {
        int a, b, x;
        scanf("%d%d%d", &a, &b, &x);

        prv[b].push_back({a, x});
    }

    memset(dp, -1, sizeof(dp));

    for (int i = 1; i <= N; i++)
        printf("%d\n", minStartTime(i));
}
