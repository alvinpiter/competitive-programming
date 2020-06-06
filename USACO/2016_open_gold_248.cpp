#include<bits/stdc++.h>
using namespace std;
#define MAXN 248

/*
dp[l][r] -> 0 if segment l..r can't be merged into single number, otherwise it is x where x
is the result of merging l..r.

The answer will be the maximum of dp[l][r].
*/

int N, num[MAXN + 3], dp[MAXN + 3][MAXN + 3];

int solve(int l, int r) {
    if (l == r)
        return num[l];

    if (dp[l][r] != -1)
        return dp[l][r];

    int best = 0;
    for (int k = l; k < r; k++) {
        int first = solve(l, k);
        int second = solve(k + 1, r);

        if (first != -1 && first == second)
            best = max(best, first + 1);
    }

    return dp[l][r] = best;
}

int main() {
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> num[i];

    memset(dp, -1, sizeof(dp));

    int maxi = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++)
            maxi = max(maxi, solve(i, j));
    }

    cout << maxi << endl;
}
