#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int main() {
    int t, n, s[MAXN + 3], dp[MAXN + 3], best;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &s[i]);

        best = 1;

        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = 1;
            for (int d = 1; d * d <= i; d++) {
                if (i % d == 0) {
                    if (s[d] < s[i]) dp[i] = max(dp[i], dp[d] + 1);
                    if (s[i/d] < s[i]) dp[i] = max(dp[i], dp[i/d] + 1);
                }
            }

            best = max(best, dp[i]);
        }

        printf("%d\n", best);
    }
}
