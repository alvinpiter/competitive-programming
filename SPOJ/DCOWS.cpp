#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 9000000000LL
#define MAXN 5000

int N, M, bulls[MAXN + 3], cows[MAXN + 3];
LL dp[MAXN + 3][MAXN + 3];

LL solve(int bullsIdx, int cowsIdx) {
    if (bullsIdx == 0)
        return 0;

    if (cowsIdx == 0)
        return INF;

    if (dp[bullsIdx][cowsIdx] != -1)
        return dp[bullsIdx][cowsIdx];

    LL skip = solve(bullsIdx, cowsIdx - 1);
    LL take = solve(bullsIdx - 1, cowsIdx - 1) + abs(bulls[bullsIdx] - cows[cowsIdx]);

    return dp[bullsIdx][cowsIdx] = min(skip, take);
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> bulls[i];

    for (int i = 1; i <= M; i++)
        cin >> cows[i];

    sort(bulls + 1, bulls + N + 1);
    sort(cows + 1, cows + M + 1);

    memset(dp, -1, sizeof(dp));

    cout << solve(N, M) << endl;
}
