/*
Very interesting problem!

Notice the area enclosed by cutting at Ai_1 to Bi_1 and Ai to Bi is:
(Ai_1 + Bi_1)/2 - (Ai + Bi)/2

Using that formula, we can generate n - 1 equations:
A1 + B1 = 2 * C1
A2 + B2 = 2 * (C1 + C2)
.
.
An_1 + Bn_1 = 2 * (C1 + C2 + .. + Cn_1)

We would like to find values such that all the equations are true and Ai_1 < Ai and Bi_1 < Bi. We can calculate it by using dynamic programming.
dp[n][l] -> number of ways to fulfill the first n (n <= 100) equations such and An is l (l <= 30000).

We can speed up the computation with the help of prefix sum to reach the final complexity of O(NL).
By using the fact that Bn_1 < Bn, we know An_1 > 2 * prefixC[n - 1] - Bn
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 100
#define MAXL 30000
#define MOD 1000000007

int N, L, prefixC[MAXN + 3];
int dp[MAXN + 3][MAXL + 3], prefixDp[MAXN + 3][MAXL + 3];

int main() {
    cin >> N >> L;

    prefixC[0] = 0;
    for (int i = 1; i <= N; i++) {
        int c;
        cin >> c;

        prefixC[i] = prefixC[i - 1] + c;
    }

    memset(prefixDp, 0, sizeof(prefixDp));

    //base case
    for (int a = 1; a <= L - 1; a++) {
        int b = 2 * prefixC[1] - a;

        if (b > 0 && b <= L - 1)
            dp[1][a] = 1;
        else
            dp[1][a] = 0;

        prefixDp[1][a] = prefixDp[1][a - 1] + dp[1][a];
    }

    for (int n = 2; n <= N - 1; n++) {
        for (int a = 1; a <= L - 1; a++) {
            int b = 2 * prefixC[n] - a;
            if (b > 0 && b <= L - 1) {
                int lowerbound = max(0, 2 * prefixC[n - 1] - b); //first invalid value
                int upperbound = min(a, 2 * prefixC[n - 1]) - 1; //last valid value

                if (lowerbound <= upperbound)
                    dp[n][a] = (prefixDp[n - 1][upperbound] - prefixDp[n - 1][lowerbound] + MOD)%MOD;
                else
                    dp[n][a] = 0;
            } else {
                dp[n][a] = 0;
            }

            prefixDp[n][a] = (prefixDp[n][a - 1] + dp[n][a])%MOD;
        }
    }

    cout << prefixDp[N - 1][L - 1] << endl;
}
