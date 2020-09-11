#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int N, K, C, dp1[MAXN + 3], dp2[MAXN + 3];
    char S[MAXN + 3];

    scanf("%d%d%d", &N, &K, &C);
    scanf("%s", S);

    dp1[0] = 0;
    for (int i = 1; i <= N; i++) {
        dp1[i] = dp1[i - 1];
        if (S[i - 1] == 'o')
            dp1[i] = max(dp1[i], 1 + dp1[max(0, i - C - 1)]);
    }

    dp2[N + 1] = 0;
    for (int i = N; i >= 1; i--) {
        dp2[i] = dp2[i + 1];
        if (S[i - 1] == 'o')
            dp2[i] = max(dp2[i], 1 + dp2[min(N + 1, i + C + 1)]);
    }

    for (int i = 1; i <= N; i++) {
        if (S[i - 1] == 'o' && dp1[i - 1] + dp2[i + 1] < K)
            printf("%d\n", i);
    }
}
