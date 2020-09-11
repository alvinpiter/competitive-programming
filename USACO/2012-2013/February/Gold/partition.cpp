#include<bits/stdc++.h>
using namespace std;
#define MAXN 15
#define INF 1000000000

int N, K, grid[MAXN + 3][MAXN + 3];
int sum[MAXN + 3][MAXN + 3], maxi[(1 << MAXN)][MAXN + 3][MAXN + 3], dp[MAXN + 3][2 * MAXN + 3], answer;

int getSum(int r1, int c1, int r2, int c2) {
    int result = sum[r2][c2];

    if (r1 > 0)
        result -= sum[r1 - 1][c2];

    if (c1 > 0)
        result -= sum[r2][c1 - 1];

    if (r1 > 0 && c1 > 0)
        result += sum[r1 - 1][c1 - 1];

    return result;
}

int main() {
    ifstream fin("partition.in");
    ofstream fout("partition.out");

    fin >> N >> K;

    memset(sum, 0, sizeof(sum));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fin >> grid[i][j];
            sum[i][j] = grid[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    //precompute
    for (int mask = 0; mask < (1 << (N - 1)); mask++) {
        for (int r1 = 0; r1 < N; r1++) {
            for (int r2 = r1; r2 < N; r2++) {
                maxi[mask][r1][r2] = 0;

                int lastFence = -1;
                for (int i = 0; i < N - 1; i++) {
                    //If i-th (0-indexed) bit of mask is on, that means there is a vertical fence after column i (0-indexed)
                    if (mask & (1 << i)) {
                        int value = getSum(r1, lastFence + 1, r2, i);
                        maxi[mask][r1][r2] = max(maxi[mask][r1][r2], value);

                        lastFence = i;
                    }
                }

                int value = getSum(r1, lastFence + 1, r2, N - 1);
                maxi[mask][r1][r2] = max(maxi[mask][r1][r2], value);
            }
        }
    }

    answer = INF;
    for (int mask = 0; mask < (1 << (N - 1)); mask++) {
        int onBit = 0;
        for (int i = 0; i < (N - 1); i++) {
            if (mask & (1 << i))
                onBit += 1;
        }

        if (onBit > K)
            continue;

        int _K = K - onBit;

        for (int i = 0; i < N; i++)
            dp[i][0] = maxi[mask][0][i];

        for (int k = 1; k <= _K; k++)
            dp[0][k] = INF;

        for (int j = 1; j < N; j++) {
            for (int k = 1; k <= _K; k++) {
                dp[j][k] = INF;
                for (int i = j; i >= 1; i--) {
                    dp[j][k] = min(dp[j][k], max(dp[i - 1][k - 1], maxi[mask][i][j]));
                }
            }
        }

        answer = min(answer, dp[N - 1][_K]);
    }

    fout << answer << endl;
}
