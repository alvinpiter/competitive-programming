#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXK 2000

/*
Observations:
* If two offers have the same x, it is better to pick the one with largest y
* Offers with x > k can't be used. So there are k offers to be considered.
* It is better to buy cheapest shovel first. So we only need to consider the first k shovel.

With those observations, the solution is dynamic programming dp[i] = min cost to buy the first i shovels.
Total complexity is O(k^2).
*/

int n, m, k, a[MAXN + 3], offer[MAXK + 3], sum[MAXK + 3], dp[MAXK + 3];

int solve(int idx) {
    if (idx == 0)
        return 0;

    if (dp[idx] != -1)
        return dp[idx];

    int withoutOffer = a[idx] + solve(idx - 1);
    int withOffer = 1e9;
    for (int off = 1; off <= idx; off++) {
        if (offer[off] != -1)
            withOffer = min(withOffer, (sum[idx] - sum[idx - (off - offer[off])]) + solve(idx - off));
    }

    return dp[idx] = min(withoutOffer, withOffer);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    memset(offer, -1, sizeof(offer));
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        if (x <= k)
            offer[x] = max(offer[x], y);
    }

    sort(a + 1, a + n + 1);

    sum[0] = 0;
    for (int i = 1; i <= k; i++)
        sum[i] = sum[i - 1] + a[i];

    memset(dp, -1, sizeof(dp));

    printf("%d\n", solve(k));
}
