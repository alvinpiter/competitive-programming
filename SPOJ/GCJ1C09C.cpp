#include<bits/stdc++.h>
using namespace std;
#define MAXQ 100
#define INF 1000000000

int N, P, Q, q[MAXQ + 3], dp[MAXQ + 3][MAXQ + 3];

int solve(int l, int r) {
    if (l == r)
        return (q[l] - q[l - 1] - 1) + (q[r + 1] - q[r] - 1);

    if (dp[l][r] != -1)
        return dp[l][r];

    int best = INF;
    for (int m = l; m <= r; m++) {
        int le = (m == l ? 0 : solve(l, m - 1));
        int ri = (m == r ? 0 : solve(m + 1, r));
        int cost = (q[m] - q[l - 1] - 1) + (q[r + 1] - q[m] - 1);

        best = min(best, cost + le + ri);
    }

    return dp[l][r] = best;
}

int main() {
    cin >> N;
    for (int cases = 1; cases <= N; cases++) {
        cin >> P >> Q;
        for (int i = 1; i <= Q; i++)
            cin >> q[i];

        q[0] = 0;
        q[Q + 1] = P + 1;

        memset(dp, -1, sizeof(dp));
        cout << "Case #" << cases << ": " << solve(1, Q) << endl;
    }
}
