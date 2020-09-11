#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define MAXH 10000

int H, N, A[MAXN + 3], B[MAXN + 3], dp[MAXH + 3];

int solve(int h) {
    if (h <= 0)
        return 0;

    if (dp[h] != -1)
        return dp[h];

    int best = 1e9;
    for (int i = 1; i <= N; i++) {
        best = min(best, B[i] + solve(h - A[i]));
    }

    return dp[h] = best;
}

int main() {
    cin >> H >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i] >> B[i];

    memset(dp, -1, sizeof(dp));

    cout << solve(H) << endl;
}
