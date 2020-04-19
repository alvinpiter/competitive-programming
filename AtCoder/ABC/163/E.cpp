#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 2000

int N;
LL dp[MAXN + 3][MAXN + 3];
pair<int, int> A[MAXN + 3];

LL solve(int l, int r) {
    if (l > r)
        return 0;

    if (dp[l][r] != -1)
        return dp[l][r];

    int idx = N - (r - l + 1) + 1;
    LL goLeft = (LL) abs(A[idx].second - l) * A[idx].first + solve(l + 1, r);
    LL goRight = (LL) abs(A[idx].second - r) * A[idx].first + solve(l, r - 1);

    return dp[l][r] = max(goLeft, goRight);
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;

        A[i] = {a, i};
    }

    sort(A + 1, A + N + 1);
    reverse(A + 1, A + N + 1);

    memset(dp, -1, sizeof(dp));

    cout << solve(1, N) << endl;
}
