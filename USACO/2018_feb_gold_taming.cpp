#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100

/*
dp[i][j] = min number of tampering on logs i..N if there should be j breakouts left (excluding breakout at i-th day)
and there is breakout at i-th day
*/

int N, a[MAXN + 3], dp[MAXN + 3][MAXN + 3];

int solve(int day, int rem) {
    if (rem == 0) {
        int tamperedCount = 0;
        for (int i = day; i <= N; i++) {
            if (a[i] != i - day)
                tamperedCount += 1;
        }

        return tamperedCount;
    }

    if (dp[day][rem] != -1)
        return dp[day][rem];

    int result = INF;
    int tamperedCount = 0;
    for (int i = day; i < N; i++) {
        if (a[i] != i - day)
            tamperedCount += 1;

        result = min(result, tamperedCount + solve(i + 1, rem - 1));
    }

    return dp[day][rem] = result;
}

int main() {
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> a[i];

    memset(dp, -1, sizeof(dp));

    for (int numBreakout = 1; numBreakout <= N; numBreakout++) {
        cout << solve(1, numBreakout - 1) << endl;
    }
}
