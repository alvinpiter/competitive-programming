#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353

int main() {
    int n, k, p, threshold, last;
    LL answer1, answer2;

    scanf("%d%d", &n, &k);

    threshold = n - k + 1;
    answer1 = 0;
    answer2 = 1;

    last = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p);

        if (p >= threshold) {
            answer1 += p;

            if (last != 0) {
                LL cnt = i - last + 1;
                answer2 = (answer2 * (cnt - 1))%MOD;
            }

            last = i;
        }
    }

    printf("%lld %lld\n", answer1, answer2);
}
