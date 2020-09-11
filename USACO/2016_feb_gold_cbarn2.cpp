#include<bits/stdc++.h>
using namespace std;
#define INF 1e15
#define LL long long int
#define MAXN 100

int n, k, r[MAXN + 3], firstUnlocked;
LL dp[MAXN + 3][10], answer;

//minimum distance cow needs to travel if we can unlock 'rem' doors and last unlocked door is 'idx'.
LL solve(int idx, int rem) {
    if (rem == 0) {
        LL currentDistanceSum = 0;
        for (int i = (idx + 1)%n, d = 1; i != firstUnlocked; i = (i + 1)%n, d++) {
            currentDistanceSum += (LL) d * r[i];
        }

        return currentDistanceSum;
    }

    if (idx == n)
        return INF;

    if (dp[idx][rem] != -1)
        return dp[idx][rem];

    LL best = INF;
    LL currentDistanceSum = 0;
    for (int i = idx + 1; i < n; i++) {
        best = min(best, currentDistanceSum + solve(i, rem - 1));
        currentDistanceSum += (LL) (i - idx) * r[i];
    }

    return dp[idx][rem] = best;
}

int main() {
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);

    scanf("%d%d", &n, &k);

    for (int i = 0; i < n; i++)
        scanf("%d", &r[i]);

    answer = INF;
    for (int f = 0; f < n; f++) {
        memset(dp, -1, sizeof(dp));

        firstUnlocked = f;
        answer = min(answer, solve(f, k - 1));
    }

    printf("%lld\n", answer);
}
