#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e15

int n, a;
LL sum, minSum;

int main() {
    scanf("%d", &n);

    sum = 0;
    minSum = INF;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a);

        sum += a;
        minSum = min(minSum, sum);
    }

    if (minSum < 0)
        printf("%lld\n", -minSum);
    else
        printf("0\n");
}
