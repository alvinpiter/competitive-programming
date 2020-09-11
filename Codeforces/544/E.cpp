#include<bits/stdc++.h>
using namespace std;

int n, k, a[5003], prv[5003], dp[5003][5003];

int solve(int idx, int rem) {
    if (idx == 0 || rem == 0)
        return 0;

    if (dp[idx][rem] != -1)
        return dp[idx][rem];

    int skip = solve(idx - 1, rem);
    int take = (idx - prv[idx]) + solve(prv[idx], rem - 1);

    return dp[idx][rem] = max(skip, take);
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    sort(a + 1, a + n + 1);

    for (int i = n; i >= 1; i--) {
        int j;
        for (j = i; j >= 1; j--) {
            if (a[i] - a[j] > 5)
                break;
        }

        prv[i] = j;
    }

    memset(dp, -1, sizeof(dp));

    cout << solve(n, k) << endl;
}
