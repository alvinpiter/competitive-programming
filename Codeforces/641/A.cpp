#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int t;
    LL n, k;

    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%lld%lld", &n, &k);

        if (n%2 == 0) {
            printf("%lld\n", n + 2 * k);
        } else {
            for (int d = 2; d <= n; d++) {
                if (n % d == 0) {
                    n += d;
                    printf("%lld\n", n + 2 * (k - 1));
                    break;
                }
            }
        }
    }
}
