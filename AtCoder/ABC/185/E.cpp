#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 1000

int N, M, A[MAXN + 3], B[MAXN + 3], dp[MAXN + 3][MAXN + 3];

int solve(int i, int j) {
    if (i == 0) {
        return j;
    }

    if (j == 0) {
        return i;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int result = (1 << 30);
    result = min(result, 1 + solve(i - 1, j));
    result = min(result, 1 + solve(i, j - 1));
    result = min(result, (A[i] == B[j] ? 0 : 1) + solve(i - 1, j - 1));

    return dp[i][j] = result;
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    for (int i = 1; i <= M; i++) {
        cin >> B[i];
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(N, M) << endl;
}
