#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, m, k;
LL prefixSum[300005], dp[300005], ans;

LL getSum(int i, int j) {
    return prefixSum[j] - prefixSum[i - 1];
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    prefixSum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        prefixSum[i] = prefixSum[i - 1] + a;
    }

    ans = 0;
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        dp[i] = 0;
        for (int len = 1; len <= m; len++) {
            if (i - len < 0) break;
            dp[i] = max(dp[i], getSum(i - len + 1, i) - k + dp[i - len]);
        }

        if (i - m >= 0) {
            dp[i] = max(dp[i], getSum(i - m + 1, i) - k + dp[i - m]);
        }

        ans = max(ans, dp[i]);
    }

    printf("%lld\n", ans);
}
