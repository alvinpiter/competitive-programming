#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

/*
dp[i][j] -> Maximum total height out of the first j student and the last student taken is at row i.

Observe that in optimal solution, there is no two consecutive columns where we don't take student at all.
*/

int main() {
    int n, h[3][MAXN + 3];
    LL dp[3][MAXN + 3], answer;

    cin >> n;
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= n; j++)
            cin >> h[i][j];
    }

    dp[0][1] = dp[0][0] = 0;

    answer = 0;
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= 2; i++) {
            dp[i][j] = h[i][j] + dp[3 - i][j - 1];
            if (j >= 2)
                dp[i][j] = max(dp[i][j], h[i][j] + dp[3 - i][j - 2]);

            answer = max(answer, dp[i][j]);
        }
    }

    cout << answer << endl;
}
