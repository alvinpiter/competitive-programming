#include<bits/stdc++.h>
using namespace std;
#define MAXN 500
#define MAXK 10

int n, k, c[MAXN * MAXK + 3], f[MAXN + 3], h[MAXK + 3];
int dp[MAXN * MAXK + 3][MAXN + 3];

int solve(int card, int player) {
    if (card == k * n + 1 || player == n + 1)
        return 0;

    if (dp[card][player] != -1)
        return dp[card][player];

    if (c[card] < f[player])
        return dp[card][player] = solve(card + 1, player);

    if (c[card] > f[player])
        return dp[card][player] = solve(card, player + 1);

    int best = 0;
    for (int i = card; i <= min(card + k - 1, n * k) && c[i] == c[card]; i++)
        best = max(best, solve(i + 1, player + 1) + h[i - card + 1]);

    return dp[card][player] = best;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n * k; i++)
        cin >> c[i];

    for (int i = 1; i <= n; i++)
        cin >> f[i];

    for(int i = 1; i <= k; i++)
        cin >> h[i];

    sort(c + 1, c + n * k + 1);
    sort(f + 1, f + n + 1);

    memset(dp, -1, sizeof(dp));

    cout << solve(1, 1) << endl;
}
