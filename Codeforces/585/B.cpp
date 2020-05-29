#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int main() {
    //dp[i][0/1] = number of sequence ending at i such that its product is positive (1) or negative (0)
    int n, a[MAXN + 3];
    LL dp[MAXN + 3][2];

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    dp[0][0] = dp[0][1] = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) {
            dp[i][1] = (1 + dp[i - 1][1]);
            dp[i][0] = dp[i - 1][0];
        } else {
            dp[i][1] = dp[i - 1][0];
            dp[i][0] = (1 + dp[i - 1][1]);
        }
    }

    LL cntNeg = 0, cntPos = 0;
    for (int i = 1; i <= n; i++) {
        cntNeg += dp[i][0];
        cntPos += dp[i][1];
    }

    cout << cntNeg << " " << cntPos << endl;
}
