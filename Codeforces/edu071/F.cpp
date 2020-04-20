#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 500000
#define SQRT 710

int q;
LL a[MAXN + 3], sum[SQRT + 3][SQRT + 3]; //sum[a][b] -> sum of all numbers at index i, where i = a (modulo b).

int main() {
    memset(a, 0, sizeof(a));
    memset(sum, 0, sizeof(sum));

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);

        if (t == 1) {
            a[x] += y;
            for (int b = 1; b <= SQRT; b++)
                sum[x%b][b] += y;
        } else {
            if (x <= SQRT) {
                printf("%lld\n", sum[y][x]);
            } else {
                LL result = 0;
                for (int i = y; i <= MAXN; i += x)
                    result += a[i];

                printf("%lld\n", result);
            }
        }
    }
}
