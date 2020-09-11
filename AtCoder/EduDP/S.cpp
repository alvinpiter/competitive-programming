#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 10000
#define MAXD 100
#define MOD 1000000007

int mod(int num, int m) {
    if (num >= 0)
        return num%m;
    else
        return (abs(num)/m + (abs(num)%m == 0 ? 0 : 1))*m + num;
}

string K;
int D;
int dp[MAXN + 3][MAXD + 3];

LL solve(string s) {
    int len = (int) s.length();

    LL ans = 0;
    LL currMod = 0;
    for (int i = 0; i < len; i++) {
        int currDigit = s[i] - '0';
        for (int dig = 0; dig < currDigit; dig++) {
            ans = (ans + dp[len - i - 1][mod(-(currMod + dig), D)])%MOD;
        }

        currMod = (currMod + currDigit)%D;
    }

    return ans;
}

int main() {
    cin >> K >> D;

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        for (int m = 0; m < D; m++) {
            for (int dig = 0; dig < 10; dig++) {
                int prvMod = mod(m - dig, D);
                dp[i][m] += dp[i - 1][prvMod];
                dp[i][m] %= MOD;
            }
        }
    }

    LL ans = solve(K);

    int sum = 0;
    for (int i = 0; i < K.length(); i++)
        sum = (sum + (K[i] - '0'))%D;

    if (sum == 0)
        ans = (ans + 1)%MOD;

    ans = (ans - 1 + MOD)%MOD; //exclude 0

    cout << ans << endl;
}
