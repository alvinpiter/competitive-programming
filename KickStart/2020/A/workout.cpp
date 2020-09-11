#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int T, N, K, M[MAXN + 3];

//Number of sessions to be added such that the gap between any two session is at most x
int f(int x) {
    int count = 0;
    for (int i = 2; i <= N; i++) {
        int gap = M[i] - M[i - 1];
        if (gap > x)
            count += (gap/x - (gap%x == 0 ? 1 : 0));
    }

    return count;
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &K);
        for (int i = 1; i <= N; i++)
            scanf("%d", &M[i]);

        int lo = 1, hi = 1e9, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (f(mid) <= K)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        printf("Case #%d: %d\n", cases, lo);
    }
}
