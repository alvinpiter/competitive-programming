#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000

int N, K, s[MAXN + 3], dp[MAXN + 3];

int main() {
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);

    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> s[i];

    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        int maxi = 0;

        dp[i] = 0;
        for (int j = i; (i - j + 1) <= K && j >= 1; j--) {
            maxi = max(maxi, s[j]);
            dp[i] = max(dp[i], dp[j - 1] + maxi * (i - j + 1));
        }
    }

    cout << dp[N] << endl;
}
