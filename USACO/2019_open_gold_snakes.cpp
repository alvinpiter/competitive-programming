#include<bits/stdc++.h>
using namespace std;
#define MAXN 400

int N, K, a[MAXN + 3], maxi[MAXN + 3][MAXN + 3], sum[MAXN + 3][MAXN + 3], dp[MAXN + 3][MAXN + 3];

int solve(int n, int k) {
    if (n == 0)
        return 0;

    if (dp[n][k] != -1)
        return dp[n][k];

    if (k == 1)
        return dp[n][k] = maxi[1][n] * n - sum[1][n];
    else {
        int best = 1e9;
        for (int i = n; i >= 1; i--) {
            best = min(best, solve(i - 1, k - 1) + maxi[i][n] * (n - i + 1) - sum[i][n]);
        }

        return dp[n][k] = best;
    }
}

int main() {
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> a[i];

    for (int i = 1; i <= N; i++) {
        maxi[i][i] = a[i];
        sum[i][i] = a[i];
        for (int j = i + 1; j <= N; j++) {
            maxi[i][j] = max(maxi[i][j - 1], a[j]);
            sum[i][j] = sum[i][j - 1] + a[j];
        }
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(N, K + 1) << endl;
}
