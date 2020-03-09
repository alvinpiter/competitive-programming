#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, x;
LL answer, dp;

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &x);
        if (i == 1) {
            answer = dp = x;
            continue;
        } else {
            dp = max(dp + x, (LL) x);
            answer = max(answer, dp);
        }
    }

    printf("%lld\n", answer);
}
