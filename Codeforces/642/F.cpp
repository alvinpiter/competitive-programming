#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e18
#define MAXN 100

int t, n, m;
LL baseHeight, h[MAXN + 3][MAXN + 3], dp[MAXN + 3][MAXN + 3];

LL solve(int r, int c) {
    if (r == n && c == m)
        return 0;

    if (dp[r][c] != -1)
        return dp[r][c];

    LL currentHeight = baseHeight + (r - 1) + (c - 1);
    LL best = INF;

    if (r < n) {
        LL costDown = h[r + 1][c] - (currentHeight + 1);
        if (costDown >= 0)
            best = min(best, costDown + solve(r + 1, c));
    }

    if (c < m) {
        LL costRight = h[r][c + 1] - (currentHeight + 1);
        if (costRight >= 0)
            best = min(best, costRight + solve(r, c + 1));
    }

    return dp[r][c] = best;
}

LL f(LL height) {
    baseHeight = height;
    memset(dp, -1, sizeof(dp));

    return (baseHeight > h[1][1] ? INF : (h[1][1] - baseHeight) + solve(1, 1));
}

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> h[i][j];
            }
        }

        LL answer = 1e18;

        //in optimal solution, at least 1 cell maintain its original height
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                answer = min(answer, f(h[i][j] - (i - 1) - (j - 1)));
            }
        }

        cout << answer << endl;
    }
}
