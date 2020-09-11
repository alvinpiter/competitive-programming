#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353
#define MAXN 3000

/*
Consider of A with size k whose sum is S:
A_x1, A_x2, ..., A_xk

This subset will contribute 2^(N - k) to the final answer.
The reason is because we have two choices (include or not) for each indices other than x1, x2, .., xk.

Let's define a dp:
dp[i][j] = Sum of 2^(N - k) for all subset of {1, 2, .., i} whose sum is j.

dp[i][j] = dp[i - 1][j] + dp[i - 1][j - A[i]]/2

The first term is obvious, that means we don't include i-th element.
The second term is quite tricky. Imagine dp[i - 1][j - A[i]] as sum of:
2^(N - k1) + 2^(N - k2) + ...

Because we add i-th element, the sum will transform to:
2^(N - (k1 + 1)) + 2^(N - (k2 + 1)) + ...
1/2 * (2^(N - k1) + 2^(N - k2) + ... )
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

int N, S, A[MAXN + 3];
LL inv2, dp[MAXN + 3][MAXN + 3];

int main() {
    cin >> N >> S;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    inv2 = fastExponentiation(2, MOD - 2);

    for (int i = 0; i <= N; i++)
        dp[i][0] = fastExponentiation(2, N);

    for (int j = 1; j <= S; j++)
        dp[0][j] = 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= S; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j >= A[i]) {
                dp[i][j] = (dp[i][j] + (dp[i - 1][j - A[i]] * inv2)%MOD)%MOD;
            }
        }
    }

    cout << dp[N][S] << endl;
}
