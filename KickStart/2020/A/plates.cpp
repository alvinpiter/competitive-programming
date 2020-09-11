#include<bits/stdc++.h>
using namespace std;
#define MAXN 50
#define MAXK 30
#define MAXP 1500

int T, N, K, P, stacks[MAXN + 3][MAXK + 3], dp[MAXN + 3][MAXP + 3];

int solve(int idx, int rem) {
    if (idx == 0)
        return (rem == 0 ? 0 : -1e9);

    if (dp[idx][rem] != -1)
        return dp[idx][rem];

    int result = solve(idx - 1, rem);
    int sum = 0;
    for (int i = 1; i <= min(rem, K); i++) {
        sum += stacks[idx][i];
        result = max(result, sum + solve(idx - 1, rem - i));
    }

    return dp[idx][rem] = result;
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d%d", &N, &K, &P);
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= K; j++)
                scanf("%d", &stacks[i][j]);
        }

        memset(dp, -1, sizeof(dp));

        printf("Case #%d: %d\n", cases, solve(N, P));
    }
}
