#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 400000

/*
Observation: There is always an optimal solution ending at the end of the month
*/

int n, d[MAXN + 3];
LL x, sumSize[MAXN + 3], sumScore[MAXN + 3];

//1 + 2 + .. + c
LL sum(LL c) {
    return (c * c + c)/2;
}

int main() {
    scanf("%d%lld", &n, &x);

    d[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &d[i]);

        sumSize[i] = d[i];
        sumScore[i] = sum(d[i]);
    }

    for (int i = n + 1; i <= 2*n; i++) {
        d[i] = d[i - n];
        sumSize[i] = sumSize[i - n];
        sumScore[i] = sumScore[i - n];
    }

    n = 2 * n;

    sumSize[0] = 0;
    sumScore[0] = 0;
    for (int i = 1; i <= n; i++) {
        sumSize[i] += sumSize[i - 1];
        sumScore[i] += sumScore[i - 1];
    }

    LL bestScore = 0;
    for (int i = 1; i <= n; i++) {
        if (sumSize[i] < x)
            continue;

        int lo = 1, hi = i, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;

            LL sz = sumSize[i] - sumSize[mid - 1];
            if (sz > x)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        LL leftOver = x - (sumSize[i] - sumSize[lo - 1]);
        LL score = (sumScore[i] - sumScore[lo - 1]) + (sum(d[lo - 1]) - sum(d[lo - 1] - leftOver));

        bestScore = max(bestScore, score);
    }

    printf("%lld\n", bestScore);
}
