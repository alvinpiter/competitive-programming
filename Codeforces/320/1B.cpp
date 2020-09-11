#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, k, x, a[MAXN + 3];
LL suffixOr[MAXN + 3], prefixOr[MAXN + 3];

int main() {
    scanf("%d%d%d", &n, &k, &x);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    prefixOr[0] = 0;
    for (int i = 1; i <= n; i++)
        prefixOr[i] = prefixOr[i - 1] | a[i];

    suffixOr[n + 1] = 0;
    for (int i = n; i >= 1; i--)
        suffixOr[i] = suffixOr[i + 1] | a[i];

    LL ans = 0;
    for (int i = 1; i <= n; i++) {
        LL current = a[i];
        for (int rep = 1; rep <= k; rep++)
            current *= x;

        ans = max(ans, prefixOr[i - 1] | current | suffixOr[i + 1]);
    }

    printf("%lld\n", ans);
}
