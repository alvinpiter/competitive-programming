#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, h[MAXN + 3];
int BIT[MAXN + 3];

void update(int idx, int val) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int H(int idx) {
    return h[idx] + query(idx);
}

//Return smallest index i such that H(i) >= val
int lowerBound(int val) {
    int lo = 1, hi = N, mid;

    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (H(mid) < val)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return lo;
}

//Return smallest index i such that H(i) > val
int upperBound(int val) {
    int lo = 1, hi = N, mid;

    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (H(mid) <= val)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return lo;
}

int main() {
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++)
        scanf("%d", &h[i]);

    sort(h + 1, h + N + 1);

    memset(BIT, 0, sizeof(BIT));
    for (int q = 1; q <= M; q++) {
        char type[2];

        scanf("%s", type);
        if (type[0] == 'F') {
            int c, h;
            scanf("%d%d", &c, &h);

            int i = lowerBound(h);
            int j = min(i + c - 1, N);

            int lb = lowerBound(H(j));
            int ub = upperBound(H(j)) - 1;
            int cnt = j - lb + 1;

            update(i, 1);
            update(lb, -1);

            update(max(1, ub - cnt + 1), 1);
            update(ub + 1, - 1);
        } else if (type[0] == 'C') {
            int mini, maxi;
            scanf("%d%d", &mini, &maxi);

            int lb = lowerBound(mini);
            int ub = upperBound(maxi);

            printf("%d\n", ub - lb);
        }
    }
}
