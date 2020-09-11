#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

/*
dp[i] -> minimum cost to change the first i garland to become k-periodic garland and the i-th is turned on.
*/

int t, n, k, prefixSum[MAXN + 3], dp[MAXN + 3];
char garland[MAXN + 3];

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &k);
        scanf("%s", garland);

        prefixSum[0] = 0;
        for (int i = 1; i <= n; i++) {
            prefixSum[i] = prefixSum[i - 1] + (garland[i - 1] - '0');
        }

        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            int currentCost = (garland[i - 1] == '1' ? 0 : 1);

            dp[i] = currentCost + prefixSum[i - 1]; //This is the last 1

            //Add another 1 to the left
            if (i >= k)
                dp[i] = min(dp[i], dp[i - k] + currentCost + (prefixSum[i - 1] - prefixSum[i - k]));
        }

        int answer = prefixSum[n]; //initialize the value as the cost to erase all 1
        for (int i = 1; i <= n; i++) {
            answer = min(answer, dp[i] + (prefixSum[n] - prefixSum[i]));
        }

        printf("%d\n", answer);
    }
}
