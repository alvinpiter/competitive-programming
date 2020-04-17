#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000
#define INF 1e15

int main() {
    int t, n, a, b;
    string s;
    LL dp[MAXN + 3][3];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> a >> b >> s;

        dp[0][1] = b;
        dp[0][2] = INF;
        for (int i = 1; i <= n; i++) {
            bool isFlexible = (s[i - 1] == '0' && (i == n || s[i] == '0'));

            if (isFlexible) {
                dp[i][1] = b + min(a + dp[i - 1][1], 2 * a + dp[i - 1][2]);
            } else {
                dp[i][1] = INF;
            }

            dp[i][2] = 2 * b + min(a + dp[i - 1][2], 2 * a + dp[i - 1][1]);
        }

        cout << dp[n][1] << endl;
    }
}
