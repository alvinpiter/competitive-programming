#include<bits/stdc++.h>
using namespace std;
#define MAXC 80
#define MAXBAL (MAXC + MAXC)*MAXC

int R, C, A[MAXC + 3][MAXC + 3], B[MAXC + 3][MAXC + 3];
bool dp[2][MAXC + 3][2 * MAXBAL + 3];

int main() {
    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
            cin >> A[i][j];
    }

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++)
            cin >> B[i][j];
    }

    memset(dp, false, sizeof(dp));

    //base case
    dp[0][0][0 + MAXBAL] = dp[1][0][0 + MAXBAL] = true;

    int t = 0;
    for (int i = 1; i <= R; i++) {
        t = 1 - t;
        for (int j = 1; j <= C; j++) {
            for (int bal = -MAXC * (i + j - 1); bal <= MAXC * (i + j - 1); bal++) {
                dp[t][j][bal + MAXBAL] = false;

                int ab = A[i][j] - B[i][j];
                int ba = -ab;

                if (i > 1) {
                    if (dp[1 - t][j][bal - ab + MAXBAL])
                        dp[t][j][bal + MAXBAL] = true;

                    if (dp[1 - t][j][bal - ba + MAXBAL])
                        dp[t][j][bal + MAXBAL] = true;
                }

                if (j > 1 || i == 1) {
                    if (dp[t][j - 1][bal - ab + MAXBAL])
                        dp[t][j][bal + MAXBAL] = true;

                    if (dp[t][j - 1][bal - ba + MAXBAL])
                        dp[t][j][bal + MAXBAL] = true;
                }
            }
        }
    }

    int answer = MAXBAL;
    for (int bal = -MAXBAL; bal <= MAXBAL; bal++) {
        if (dp[t][C][bal + MAXBAL])
            answer = min(answer, abs(bal));
    }

    cout << answer << endl;
}
