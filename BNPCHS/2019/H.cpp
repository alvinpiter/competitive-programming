#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 10000

int T, N, M, X[MAXN + 3];

//Is it possible to divide the problems into M groups such that the total within each group is at most threshold
bool check(LL threshold) {
    int numGroup = 1;
    LL currentSum = 0;

    for (int i = 1; i <= N; i++) {
        if (X[i] > threshold)
            return false;

        if (currentSum + X[i] > threshold) {
            numGroup += 1;
            currentSum = X[i];
        } else {
            currentSum += X[i];
        }
    }

    return (numGroup <= M);
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &M);
        for (int i = 1; i <= N; i++)
            scanf("%d", &X[i]);

        LL lo = 1, mid, hi = 1000000000000LL;
        while (hi >= lo) {
            mid = (lo + hi)/2;

            if (check(mid))
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        printf("Case #%d: %lld\n", cases, lo);
    }
}
