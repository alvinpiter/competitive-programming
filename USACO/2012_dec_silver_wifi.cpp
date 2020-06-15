#include<bits/stdc++.h>
using namespace std;
#define MAXN 2000

int N, A, B, pos[MAXN + 3];
double dp[MAXN + 3]; //dp[j] -> minimum cost to cover the first j cows

int main() {
    freopen("wifi.in", "r", stdin);
    freopen("wifi.out", "w", stdout);

    cin >> N >> A >> B;

    for (int i = 1; i <= N; i++)
        cin >> pos[i];

    sort(pos + 1, pos + N + 1);

    dp[0] = 0;
    for (int j = 1; j <= N; j++) {
        dp[j] = 1e9;
        for (int i = j; i >= 1; i--) {
            dp[j] = min(dp[j], dp[i - 1] + A + B*((pos[j] - pos[i])/2.0));
        }
    }

    if (dp[N] - floor(dp[N]) < 1e-6)
        printf("%.0lf\n", dp[N]);
    else
        printf("%.1lf\n", dp[N]);
}
