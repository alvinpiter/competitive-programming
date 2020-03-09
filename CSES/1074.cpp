#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, p[MAXN + 3];
LL answer, prefixSum[MAXN + 3], suffixSum[MAXN + 3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &p[i]);

    sort(p + 1, p + n + 1);

    prefixSum[0] = 0;
    for (int i = 1; i <= n; i++)
        prefixSum[i] = prefixSum[i - 1] + p[i];

    suffixSum[n + 1] = 0;
    for (int i = n; i >= 1; i--)
        suffixSum[i] = suffixSum[i + 1] + p[i];

    answer = 1e16;
    for (int i = 1; i <= n; i++) {
        LL prefixCost = (LL) p[i] * (i - 1) - prefixSum[i - 1];
        LL suffixCost = suffixSum[i + 1] - (LL) p[i] * (n - i);

        answer = min(answer, prefixCost + suffixCost);
    }

    printf("%lld\n", answer);


}
