#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000

int T, N, a[MAXN + 3], b[MAXN + 3];
LL dp[MAXN + 3][3];

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
            scanf("%d%d", &a[i], &b[i]);

        for (int j = 0; j < 3; j++) {
            dp[1][j] = (LL) j * b[1];
        }

        for (int i = 2; i <= N; i++) {
            for (int j = 0; j < 3; j++) {
                dp[i][j] = 1e18;
                for (int k = 0; k < 3; k++) {
                    if (a[i - 1] + k != a[i] + j)
                        dp[i][j] = min(dp[i][j], dp[i - 1][k] + (LL) j * b[i]);
                }
            }
        }

        printf("%lld\n", min(dp[N][0], min(dp[N][1], dp[N][2])));
    }
}
