#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000000
#define MOD 1000000007

/*
The painting is valid if there is K consecutive colors.
It is easier to count the number of segment that does not have K consecutive colors.

dp[n] = number of ways to paint n cells such that there is no K consecutive colors
dp[n] = (M - 1)*sum(dp[n - cnt], 1 <= cnt < K), base case is when n < K.

Can be speed up using prefix sum.
*/

LL fastExponentiation(LL base, int p) {
    LL result = 1;
    while (p > 0) {
        if (p%2 == 1)
            result = (result * base)%MOD;

        base = (base * base)%MOD;
        p /= 2;
    }

    return result;
}

int N, M, K;
LL dp[MAXN + 3], sumDp[MAXN + 3];

int main() {
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);

    cin >> N >> M >> K;

    sumDp[0] = 0;
    for (int i = 1; i < K; i++) {
        dp[i] = fastExponentiation(M, i);
        sumDp[i] = (sumDp[i - 1] + dp[i])%MOD;
    }

    for (int i = K; i <= N; i++) {
        dp[i] = (sumDp[i - 1] - sumDp[i - K])*(M - 1);
        dp[i] %= MOD;

        sumDp[i] = (sumDp[i - 1] + dp[i])%MOD;
    }

    LL all = fastExponentiation(M, N);

    cout << (all - dp[N] + MOD)%MOD << endl;
}
