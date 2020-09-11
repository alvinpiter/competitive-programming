#include<bits/stdc++.h>
using namespace std;
#define SQRT 300

/*
Define dp[i][j] as the max number of gems reachable from index i to n if the last jump length was j. This dp will TLE.

Observation: There are not so many jump length that we need to consider.
Proof: Assume we want to calculate the maximum jump length. To achieve this, we have to always do +1 jump.
d + (d + 1) + (d + 2) + (d + 3) + ... + (d + x) <= 30000
x will be around sqrt(2 * 30000). We will use x = 300 to be safe.

Calculating the minimum jump length can be done similarly.

Re-define dp[i][j] as the max number of gems reachable from index i to n if the last jump length was d + j.
j will range from -300 to 300.
*/

int n, d, cnt[30003], dp[30003][2 * SQRT + 3];

int solve(int i, int j) {
    if (i > 30000)
        return 0;

    if (dp[i][j + SQRT] != -1)
        return dp[i][j + SQRT];

    int lastJumpLength = d + j;
    int best = 0;

    best = max(best, cnt[i] + solve(i + lastJumpLength, j)); //+0
    best = max(best, cnt[i] + solve(i + lastJumpLength + 1, j + 1)); //+1

    //-1
    if (d + j > 1)
        best = max(best, cnt[i] + solve(i + lastJumpLength - 1, j - 1));

    return dp[i][j + SQRT] = best;
}

int main() {
    cin >> n >> d;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;

        cnt[p] += 1;
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(d, 0) << endl;
}
