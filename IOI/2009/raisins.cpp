#include<bits/stdc++.h>
using namespace std;
#define MAXN 50

int N, M, sum[MAXN + 3][MAXN + 3], dp[MAXN + 3][MAXN + 3][MAXN + 3][MAXN + 3];

int solve(int r1, int c1, int r2, int c2) {
    if (r1 == r2 && c1 == c2)
        return 0;

    if (dp[r1][c1][r2][c2] != -1)
        return dp[r1][c1][r2][c2];

    int best = 1e9;
    int cost = sum[r2][c2] - sum[r1 - 1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];

    //vertical cut
    for (int j = c1; j < c2; j++) {
        best = min(best, cost + solve(r1, c1, r2, j) + solve(r1, j + 1, r2, c2));
    }

    //horizontal cut
    for (int i = r1; i < r2; i++) {
        best = min(best, cost + solve(r1, c1, i, c2) + solve(i + 1, c1, r2, c2));
    }

    return dp[r1][c1][r2][c2] = best;
}

int main() {
    cin >> N >> M;

    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int num;
            cin >> num;

            sum[i][j] += num;
            sum[i][j] += sum[i - 1][j];
            sum[i][j] += sum[i][j - 1];
            sum[i][j] -= sum[i - 1][j - 1];
        }
    }

    memset(dp, -1, sizeof(dp));

    cout << solve(1, 1, N, M) << endl;
}
