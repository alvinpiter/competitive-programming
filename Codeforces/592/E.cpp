#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

/*
Observation: Assume L and R are the minimum and maximum height after operations. Either L or R must be one of ai.
Proof:
WLOG, picture ai sorted non-decreasingly. Assume in optimal solution, ai < L < ai+1 and aj < R < aj+1.
Let numLarge is number of ai > R and numSmall is number of ai < L. There will be 3 cases:
* numLarge = numSmall -> We can move range L-R up or down
* numLarge > numSmall -> We can move range L-R up
* numLarge < numSmall -> We can move range L-R down
*/

int n, a[MAXN + 3], sortedA[MAXN + 3], answer;
LL k, prefixSum[MAXN + 3];

//{number, sum} of a which is smaller than h
pair<int, LL> statsSmaller(int h) {
    int pos = lower_bound(sortedA + 1, sortedA + n + 1, h) - sortedA;
    return make_pair(pos - 1, prefixSum[pos - 1]);
}

//{number, sum} of a which is larger than h
pair<int, LL> statsLarger(int h) {
    int pos = upper_bound(sortedA + 1, sortedA + n + 1, h) - sortedA;
    return make_pair(n - pos + 1, prefixSum[n] - prefixSum[pos - 1]);
}

int main() {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        sortedA[i] = a[i];
    }

    answer = 2e9;

    sort(sortedA + 1, sortedA + n + 1);

    prefixSum[0] = 0;
    for (int i = 1; i <= n; i++)
        prefixSum[i] = prefixSum[i - 1] + sortedA[i];

    //Fix ai as L
    for (int i = 1; i <= n; i++) {
        LL opsLeft = k;

        pair<int, LL> statSmall = statsSmaller(a[i]);
        opsLeft -= ((LL) a[i] * statSmall.first - statSmall.second);

        if (opsLeft <= 0)
            continue;

        int lo = a[i], hi = 1e9, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;

            pair<int, LL> statLarge = statsLarger(mid);
            LL cost = statLarge.second - (LL) mid * statLarge.first;

            if (cost <= opsLeft)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        answer = min(answer, lo - a[i]);
    }

    //Fix ai as R
    for (int i = 1; i <= n; i++) {
        LL opsLeft = k;

        pair<int, LL> statLarge = statsLarger(a[i]);
        opsLeft -= (statLarge.second - (LL) a[i] * statLarge.first);

        if (opsLeft <= 0)
            continue;

        int lo = 0, hi = a[i], mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;

            pair<int, LL> statSmall = statsSmaller(mid);
            LL cost = (LL) mid * statSmall.first - statSmall.second;

            if (cost <= opsLeft)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        answer = min(answer, a[i] - hi);
    }

    printf("%d\n", answer);
}
