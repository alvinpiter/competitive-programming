#include<bits/stdc++.h>
using namespace std;

int N, H, L, R, a[2003], dp[2003][2003];

//Max number of good sleep can be achieved considering sleep number n to N and currently at time h
int solve(int n, int h) {
    if (n == N + 1)
        return 0;

    if (dp[n][h] != -1)
        return dp[n][h];

    int sleepTime1 = (h + a[n])%H;
    int ans1 = solve(n + 1, sleepTime1) + (sleepTime1 >= L && sleepTime1 <= R ? 1 : 0);

    int sleepTime2 = (h + a[n] - 1)%H;
    int ans2 = solve(n + 1, sleepTime2) + (sleepTime2 >= L && sleepTime2 <= R ? 1 : 0);

    return dp[n][h] = max(ans1, ans2);
}

int main() {
    cin >> N >> H >> L >> R;
    for (int i = 1; i <= N; i++)
        cin >> a[i];

    memset(dp, -1, sizeof(dp));

    cout << solve(1, 0) << endl;
}
