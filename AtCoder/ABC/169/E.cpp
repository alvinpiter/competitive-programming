#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 200000

/*
Consider N is odd. Solution for N is even is similar.

Assume the ranges are sorted based in non-decreasing order of A.
The minimal value for the median must be A[(N + 1)/2].
If it is smaller than this, then there will be too many larger than the median.

To find the maximum value for the median, we can do binary search.
Assume the maximal value is mid. There must be at most (N + 1)/2 - 1 numbers that is surely smaller than mid.
i.e, the number of ranges that ends before mid must be at most (N + 1)/2 - 1.
*/

int N, suffixMinB[MAXN + 3];
pair<int, int> ranges[MAXN + 3];

//find a number such that there are at most 'threshold' number that is surely smaller than it
int upper(int starting, int threshold) {
    int lo = starting, hi = INF, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        int smaller = 0;
        for (int i = 1; i <= N; i++) {
            if (ranges[i].second < mid)
                smaller += 1;
        }

        if (smaller > threshold)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    return hi;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d%d", &ranges[i].first, &ranges[i].second);

    sort(ranges + 1, ranges + N + 1);

    suffixMinB[N] = ranges[N].second;
    for (int i = N - 1; i >= 1; i--)
        suffixMinB[i] = min(ranges[i].second, suffixMinB[i + 1]);

    if (N%2 == 1) {
        int smallest = ranges[(N + 1)/2].first;
        int largest = upper(smallest, (N + 1)/2 - 1);

        printf("%d\n", largest - smallest + 1);
    } else {
        int l1 = ranges[N/2].first;
        int r1 = upper(l1, N/2 - 1);
        int l2 = ranges[N/2 + 1].first;
        int r2 = upper(l2, N/2);

        printf("%d\n", (r1 + r2) - (l1 + l2) + 1);
    }
}
