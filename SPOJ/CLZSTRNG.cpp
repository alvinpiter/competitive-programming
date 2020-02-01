#include<bits/stdc++.h>
using namespace std;
#define MAXN 100
#define LL long long int
#define MOD 1000000009

LL C[MAXN + 3][MAXN + 3], dp[MAXN + 3][MAXN + 3][MAXN + 3];
int T, K, M;
string s1, s2;

/*
Returns number of ways to reach (0, 0) from (numZero, numOne) in k steps.
*/
LL solve(int numZero, int numOne, int k) {
    if (k == 0) {
        if (numOne == 0)
            return 1;
        else
            return 0;
    }

    if (dp[numZero][numOne][k] != -1)
        return dp[numZero][numOne][k];

    LL result = 0;

    /*
    Toggle i zeroes and m - i ones.
    */
    for (int i = 0; i <= min(M, numZero); i++) {
        if (numOne < M - i)
            continue;

        LL numWaysToTakeZeros = C[numZero][i];
        LL numWaysToTakeOnes = C[numOne][M - i];
        LL totalWays = ((numWaysToTakeZeros * numWaysToTakeOnes)%MOD) * (solve(numZero - i + (M - i), numOne - (M - i) + i, k - 1))%MOD;

        result = (result + totalWays)%MOD;
    }

    return dp[numZero][numOne][k] = result;
}

int main() {
    for (int j = 0; j <= MAXN; j++)
        C[0][j] = 0;

    for (int i = 0; i <= MAXN; i++)
        C[i][0] = 1;

    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= MAXN; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1])%MOD;
        }
    }

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> s1 >> s2 >> M >> K;

        int numZero = 0, numOne = 0;
        for (int i = 0; i < s1.length(); i++) {
            if (s1[i] == s2[i])
                numZero += 1;
            else
                numOne += 1;
        }

        memset(dp, -1, sizeof(dp));
        cout << solve(numZero, numOne, K) << endl;
    }
}
