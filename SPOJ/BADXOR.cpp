#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 100000007

int T, N, M, A[1003], B[1003];
LL dp[1003][(1 << 11) + 3];

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> M;

        for (int i = 1; i <= N; i++)
            cin >> A[i];

        for (int i = 1; i <= M; i++)
            cin >> B[i];

        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;

        for (int i = 1; i <= N; i++) {
            for (int mask = 0; mask < (1 << 11); mask++)
                dp[i][mask] = (dp[i - 1][mask] + dp[i - 1][mask ^ A[i]])%MOD;
        }

        LL numSubsets = 1;
        for (int i = 1; i <= N; i++)
            numSubsets = (2 * numSubsets)%MOD;

        LL numInvalids = 0;
        for (int i = 1; i <= M; i++)
            numInvalids = (numInvalids + dp[N][B[i]])%MOD;

        LL numValids = (numSubsets - numInvalids + MOD)%MOD;

        cout << "Case " << cases << ": " << numValids << endl;
    }
}
