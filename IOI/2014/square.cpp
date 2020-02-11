#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int N, grid[MAXN + 3][MAXN + 3], dp[MAXN + 3][MAXN + 3], maxSize, counter;

int main() {
    cin >> N;

    memset(dp, 0, sizeof(dp));

    maxSize = 0;
    counter = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 0) {
                dp[i][j] = 0;
                continue;
            } else {
                dp[i][j] = 1;

                int sz1 = dp[i - 1][j];
                int sz2 = dp[i][j - 1];

                if (sz1 > 0 && sz2 > 0) {
                    if (sz1 != sz2)
                        dp[i][j] = min(sz1, sz2) + 1;
                    else
                        dp[i][j] = (grid[i - sz1][j - sz2] == 1 ? sz1 + 1 : sz1);
                }
            }

            if (dp[i][j] > maxSize) {
                maxSize = dp[i][j];
                counter = 1;
            } else if (dp[i][j] == maxSize)
                counter += 1;
        }
    }

    cout << maxSize * counter << endl;
}
