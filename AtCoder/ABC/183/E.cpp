#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 2000

/*
Prefix sum DP.
Use (i - j) + max(H, W) and j to refer to a point diagonally.
*/

int prevInCol[MAXN + 3], prevInRow[MAXN + 3], prevInDiagonal[2 * MAXN + 3];
int dp[MAXN + 3][MAXN + 3], sumInCol[MAXN + 3][MAXN + 3], sumInRow[MAXN + 3][MAXN + 3], sumInDiagonal[MAXN + 3][MAXN + 3];
int H, W;

int main() {
    cin >> H >> W;

    memset(prevInCol, 0, sizeof(prevInCol));
    memset(prevInRow, 0, sizeof(prevInRow));

    for (int j = 1; j <= W; j++) {
        int d = (1 - j) + max(H, W);
        prevInDiagonal[d] = j - 1;
    }

    for (int i = 1; i <= H; i++) {
        int d = (i - 1) + max(H, W);
        prevInDiagonal[d] = 0;
    }

    memset(sumInCol, 0, sizeof(sumInCol));
    memset(sumInRow, 0, sizeof(sumInRow));
    memset(sumInDiagonal, 0, sizeof(sumInDiagonal));

    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            char c;
            cin >> c;

            int d = (i - j) + max(H, W);

            if (c == '#') {
                dp[i][j] = 0;

                prevInCol[j] = i;
                prevInRow[i] = j;
                prevInDiagonal[d] = j;
            } else {
                if (i == 1 && j == 1) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = 0;
                    dp[i][j] = (dp[i][j] + (sumInCol[j][i - 1] - sumInCol[j][prevInCol[j]] + MOD)%MOD)%MOD;
                    dp[i][j] = (dp[i][j] + (sumInRow[i][j - 1] - sumInRow[i][prevInRow[i]] + MOD)%MOD)%MOD;
                    dp[i][j] = (dp[i][j] + (sumInDiagonal[d][j - 1] - sumInDiagonal[d][prevInDiagonal[d]] + MOD)%MOD)%MOD;
                }
            }

            sumInCol[j][i] = (sumInCol[j][i - 1] + dp[i][j])%MOD;
            sumInRow[i][j] = (sumInRow[i][j - 1] + dp[i][j])%MOD;
            sumInDiagonal[d][j] = (sumInDiagonal[d][j - 1] + dp[i][j])%MOD;
        }
    }

    cout << dp[H][W] << endl;
}
