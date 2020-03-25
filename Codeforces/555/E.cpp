#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, A[MAXN + 3], B[MAXN + 3];
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

int rangeSum(int l, int r) {
    if (l <= r)
        return query(r) - query(l - 1);
    else
        return (query(N) - query(l - 1)) + query(r);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &A[i]);

    memset(BIT, 0, sizeof(BIT));
    for (int i = 1; i <= N; i++) {
        int b;
        scanf("%d", &b);

        update(b + 1, 1); //Convert to 1-based index
    }

    for (int i = 1; i <= N; i++) {
        int l = (N - A[i])%N;

        int lo = 1, hi = N, mid;
        while (hi >= lo) {
            int mid = (lo + hi)/2;

            int r = (l + mid - 1)%N;
            int count = rangeSum(l + 1, r + 1); //Convert to 1-based index

            if (count > 0)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        int takenIndex = (l + lo - 1)%N;

        B[i] = takenIndex;
        update(takenIndex + 1, - 1);
    }

    for (int i = 1; i <= N; i++) {
        printf("%d ", (A[i] + B[i])%N);
    }
    cout << endl;
}
