#include<bits/stdc++.h>
using namespace std;
#define MAXV 1000000

int n, cnt[MAXV + 3], dp[MAXV + 3];

int main() {
    scanf("%d", &n);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        cnt[a] += 1;
    }

    for (int i = MAXV; i >= 1; i--) {
        dp[i] = cnt[i];
        for (int j = 2 * i; j <= MAXV; j += i)
            dp[i] = max(dp[i], cnt[i] + dp[j]);
    }

    int answer = 0;
    for (int i = 1; i <= MAXV; i++) answer = max(answer, dp[i]);

    printf("%d\n", answer);
}
