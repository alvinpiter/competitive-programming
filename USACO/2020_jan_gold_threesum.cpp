#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 5000
#define MAXA 1000000

int N, Q, A[MAXN + 3], cnt[2 * MAXA + 3];
int dp[MAXN + 3][MAXN + 3]; //dp[l][r] -> how many m such that l < m < r and sl + sm + sr = 0
int sumDp[MAXN + 3][MAXN + 3]; //sumDp[l][r] -> sum of all dp[a][b], where l <= a <= b <= r

int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);

    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++)
        scanf("%d", &A[i]);

    memset(cnt, 0, sizeof(cnt));
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            int target = -(A[i] + A[j]);
            if (target >= -MAXA && target <= MAXA)
                dp[i][j] = cnt[target + MAXA];

            cnt[A[j] + MAXA] += 1;
        }

        //undo changes
        for (int j = i + 1; j <= N; j++)
            cnt[A[j] + MAXA] -= 1;
    }

    //sumDp[l][r] = sumDp[l][r - 1] + sumDp[l + 1][r] - sumDp[l + 1][r - 1] + dp[l][r]
    memset(sumDp, 0, sizeof(sumDp));
    for (int hop = 1; hop <= N - 1; hop++) {
        for (int l = 1; l + hop <= N; l++) {
            int r = l + hop;
            sumDp[l][r] = sumDp[l][r - 1] + sumDp[l + 1][r] - sumDp[l + 1][r - 1] + dp[l][r];
        }
    }

    for (int i = 1; i <= Q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        printf("%lld\n", sumDp[l][r]);
    }
}
