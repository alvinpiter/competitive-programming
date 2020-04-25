#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 1000

/*
dp[i] -> number of ways to draw all the balls with color <= i
dp[i] = dp[i - 1] * (number of ways to divide cnt[i] - 1 balls into sumCnt[i - 1] + 1 bags)
*/

int k, cnt[MAXN + 3], sumCnt[MAXN + 3];
LL C[MAXN + 3][MAXN + 3], dp[MAXN + 3];

int main() {
    cin >> k;

    sumCnt[0] = 0;
    for (int i = 1; i <= k; i++) {
        cin >> cnt[i];
        sumCnt[i] = sumCnt[i - 1] + cnt[i];
    }

    for (int j = 1; j <= MAXN; j++)
        C[0][j] = 0;

    for (int i = 0; i <= MAXN; i++)
        C[i][0] = 1;

    for (int i = 1; i <= MAXN; i++) {
        for (int j = 1; j <= MAXN; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1])%MOD;
    }

    dp[1] = 1;
    for (int i = 2; i <= k; i++) {
        int balls = cnt[i] - 1;
        int bags = sumCnt[i - 1] + 1;
        dp[i] = (dp[i - 1] * C[balls + bags - 1][bags - 1])%MOD;
    }

    cout << dp[k] << endl;
}
