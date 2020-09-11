#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

/*
Assume we choose k dragon lairs, located at indices i1, i2, .. ik.
Our profit is:
(a_i1 - 1) + (a_i2 - 2) + .. + (a_ik - k)

In order for this choice to be optimal, whenever we remove one of the index, it must result to lower profit.
Assume we want to remove i1. The profit will change by -(a_i1 - 1) + (k - 1), and it must be negative, which yield a_i1 >= k.

So, in optimal choice of size k, all chosen numbers must be >= k.
*/

int main() {
    int n, a[MAXN + 3];
    LL sum, sumCost, maxProfit;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    sort(a + 1, a + n + 1);

    maxProfit = 0;
    sum = sumCost = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] < n - i + 1)
            break;

        sum += a[i];
        sumCost += (n - i + 1);

        maxProfit = max(maxProfit, sum - sumCost);
    }

    printf("%lld\n", maxProfit);
}
