#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    /*
    sum[i] = sum(f1, f2, .., fi)
    maxSum[i] = maximum sum of segment with length at most k that ends before or at i
    */

    int n, k, sum[MAXN + 3], maxSum[MAXN + 3];

    scanf("%d%d", &n, &k);

    sum[0] = 0;
    for (int i = 1; i <= n; i++) {
        int f;
        scanf("%d", &f);

        sum[i] = sum[i - 1] + f;
        maxSum[i] = (i <= k ? sum[i] : max(maxSum[i - 1], sum[i] - sum[i - k]));
    }

    if (2 * k >= n)
        printf("%d\n", sum[n]);
    else {
        int maxi = sum[k];
        for (int i = k + 1; i <= n; i++)
            maxi = max(maxi, (sum[i] - sum[i - k]) + maxSum[i - k]);

        printf("%d\n", maxi);
    }
}
