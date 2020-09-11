#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define MOD 2012

/*
dp[i][openH][openG] -> number of ways to assign breed to the first i cows
such that there will be openH unmatched opening for Holsteins and openG
unmatched opening for Guernseys.

We can drop one of the dp state (openH or openG) by calculating some kind
of prefix on the string. If we know there are x openings in prefix i and openH of
them belongs to Holstens, then x - openH of them belongs to Guernseys.

The answer is dp[N][0];
*/

int N, prefixOpen[MAXN + 3], dp[MAXN + 3][MAXN + 3];
string S;

int main() {
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);

    cin >> S;

    N = (int) S.length();

    prefixOpen[0] = 0;
    for (int i = 1; i <= N; i++) {
        if (S[i - 1] == '(')
            prefixOpen[i] = prefixOpen[i - 1] + 1;
        else
            prefixOpen[i] = prefixOpen[i - 1] - 1;
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    for (int i = 1; i <= N; i++) {
        for (int openH = 0; openH <= N; openH++) {
            int openG = prefixOpen[i] - openH;
            if (openG < 0)
                continue;

            if (S[i - 1] == '(') {
                //assign to Holstein
                if (openH > 0)
                    dp[i][openH] += dp[i - 1][openH - 1];

                //assign to Guernseys
                if (openG > 0)
                    dp[i][openH] += dp[i - 1][openH];
            }

            if (S[i - 1] == ')') {
                //assign to Holstein
                if (openH < N)
                    dp[i][openH] += dp[i - 1][openH + 1];

                //assign to Guernseys
                if (openG < N)
                    dp[i][openH] += dp[i - 1][openH];
            }

            dp[i][openH] %= MOD;
        }
    }

    cout << dp[N][0] << endl;
}
