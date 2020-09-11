#include<bits/stdc++.h>
using namespace std;
#define INF 2000000000
#define MAXN 1001

/*
dp[i][j][last] -> minimum cost to calm cow 1..i and cow j..n where the
last cow calmed is at i + 1 (last == 0) or j - 1 (last == 1)
*/

int N, pos[MAXN + 3], dp[MAXN + 3][MAXN + 3][2];

int solve(int l, int r, int last) {
    if (l == 0 && r == N + 1)
        return 0;

    if (dp[l][r][last] != -1)
        return dp[l][r][last];

    int best = INF;
    int idx = (last == 0 ? l + 1 : r - 1);
    if (l > 0) {
        best = min(best, (l + (N - r + 1))*(pos[idx] - pos[l]) + solve(l - 1, r, 0));
    }

    if (r < N + 1) {
        best = min(best, (l + (N - r + 1))*(pos[r] - pos[idx]) + solve(l, r + 1, 1));
    }

    return dp[l][r][last] = best;
}

int main() {
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);

    cin >> N;

    N += 1;
    pos[1] = 0;
    for (int i = 2; i <= N; i++) {
        cin >> pos[i];
    }

    sort(pos + 1, pos + N + 1);

    int startingIndex;
    for (int i = 1; i <= N; i++) {
        if (pos[i] == 0)
            startingIndex = i;
    }

    memset(dp, -1, sizeof(dp));

    cout << solve(startingIndex - 1, startingIndex + 1, 0) << endl;
}
