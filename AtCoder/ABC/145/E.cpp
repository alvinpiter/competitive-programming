#include<bits/stdc++.h>
using namespace std;
#define MAXN 3000

int N, T, A[MAXN + 3], B[MAXN + 3], dp[MAXN + 3][MAXN + 3][2];

int solve(int idx, int timeLeft, int hasTakenLastMeal) {
    if (idx == N + 1)
        return 0;

    if (dp[idx][timeLeft][hasTakenLastMeal] != -1)
        return dp[idx][timeLeft][hasTakenLastMeal];

    int takeLastMeal = (hasTakenLastMeal == 0 ? B[idx] + solve(idx + 1, timeLeft, 1) : 0);
    int take = (timeLeft >= A[idx] ? B[idx] + solve(idx + 1, timeLeft - A[idx], hasTakenLastMeal) : 0);
    int leave = solve(idx + 1, timeLeft, hasTakenLastMeal);

    return dp[idx][timeLeft][hasTakenLastMeal] = max(takeLastMeal, max(take, leave));
}

int main() {
    cin >> N >> T;
    for (int i = 1; i <= N; i++)
        cin >> A[i] >> B[i];

    memset(dp, -1, sizeof(dp));

    cout << solve(1, T - 1, 0) << endl;
}
