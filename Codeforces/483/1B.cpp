#include<bits/stdc++.h>
using namespace std;
#define MAXN 5000

/*
Visualize the function as a pyramid, where a1, a2, .., an are on the base.

dp[i][j] = f(a[i] .. a[j])
maxi[i][j] = max of dp[a][b], where i <= a <= b <= j.

dp[i][j] = dp[i][j - 1] ^ dp[i + 1][j]
maxi[i][j] = max(maxi[i][j - 1], maxi[i + 1][j], dp[i][j])
*/

int n, q, dp[MAXN + 3][MAXN + 3], maxi[MAXN + 3][MAXN + 3];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        dp[i][i] = maxi[i][i] = a;
    }

    for (int d = 1; d < n; d++) {
        for (int i = 1; i + d <= n; i++) {
            int j = i + d;
            dp[i][j] = dp[i][j - 1] ^ dp[i + 1][j];
            maxi[i][j] = max(max(maxi[i][j - 1], maxi[i + 1][j]), dp[i][j]);
        }
    }

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        printf("%d\n", maxi[l][r]);
    }
}
