#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, k, x[MAXN + 3], maxX;

int main() {
    scanf("%d%d", &n, &k);

    maxX = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x[i]);
        maxX = max(maxX, x[i]);
    }

    LL lo = maxX, hi = 1e15, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        int numGroup = 1;
        LL sum = 0;
        for (int i = 1; i <= n; i++) {
            if (sum + x[i] > mid) {
                numGroup += 1;
                sum = x[i];
            } else
                sum += x[i];
        }

        if (numGroup > k)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    printf("%lld\n", lo);
}
