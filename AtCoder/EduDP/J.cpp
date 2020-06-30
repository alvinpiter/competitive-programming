#include<bits/stdc++.h>
using namespace std;
#define MAXN 300

int N, cnt[4];
double dp[MAXN + 3][MAXN + 3][MAXN + 3];

double solve(int cnt1, int cnt2, int cnt3) {
    if (cnt1 + cnt2 + cnt3 == 0)
        return 0;

    if (dp[cnt1][cnt2][cnt3] > -1)
        return dp[cnt1][cnt2][cnt3];

    double result = 1;
    if (cnt1 > 0)
        result += ((1.0 * cnt1)/N) * solve(cnt1 - 1, cnt2, cnt3);

    if (cnt2 > 0)
        result += ((1.0 * cnt2)/N) * solve(cnt1 + 1, cnt2 - 1, cnt3);

    if (cnt3 > 0)
        result += ((1.0 * cnt3)/N) * solve(cnt1, cnt2 + 1, cnt3 - 1);

    result = result * (1.0 * N)/(cnt1 + cnt2 + cnt3); //If after rolling dice we end up at the same state

    return dp[cnt1][cnt2][cnt3] = result;
}

int main() {
    cin >> N;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;

        cnt[a] += 1;
    }

    memset(dp, -1, sizeof(dp));

    printf("%.10lf\n", solve(cnt[1], cnt[2], cnt[3]));
}
