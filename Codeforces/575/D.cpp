#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int id(char c) {
    if (c == 'R') return 0;
    if (c == 'G') return 1;
    if (c == 'B') return 2;
}

int q, n, k, dp[MAXN + 3][3];
char s[MAXN + 3];

int main() {
    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d%d", &n, &k);
        scanf("%s", s);

        //base case
        for (int j = 0; j < 3; j++)
            dp[0][j] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                dp[i][j] = (id(s[i - 1]) == j ? 0 : 1) + dp[i - 1][(j - 1 + 3)%3];
            }
        }

        int best = n;
        for (int i = k; i <= n; i++) {
            for (int j = 0; j < 3; j++) {
                int cost = dp[i][j] - dp[i - k][(j - (k%3) + 3)%3];
                best = min(best, cost);
            }
        }

        printf("%d\n", best);
    }
}
