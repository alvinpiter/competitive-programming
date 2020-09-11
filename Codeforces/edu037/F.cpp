#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXV 1000000
#define MAXN 300000
#define DEBUG true

int numDiv[MAXV + 3];

void precalculateNumDiv() {
    memset(numDiv, 0, sizeof(numDiv));

    for (int i = 1; i <= MAXV; i++) {
        for (int j = i; j <= MAXV; j += i)
            numDiv[j] += 1;
    }
}

int N, M, A[MAXN + 3];
LL BIT[MAXN + 3];
set<int> notConvergedYet;

void update(int idx, int val) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

LL query(int idx) {
    LL result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

LL rsq(int a, int b) {
    return query(b) - query(a - 1);
}

int main() {
    precalculateNumDiv();

    memset(BIT, 0, sizeof(BIT));

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);

        if (numDiv[A[i]] > 1)
            notConvergedYet.insert(i);

        update(i, A[i]);
    }

    vector<int> toBeRemoved;
    for (int q = 1; q <= M; q++) {
        int t, l, r;
        scanf("%d%d%d", &t, &l, &r);

        if (t == 1) {
            toBeRemoved.clear();
            for (auto ptr = notConvergedYet.lower_bound(l); ptr != notConvergedYet.upper_bound(r); ++ptr) {
                int idx = *ptr;

                update(idx, numDiv[A[idx]] - A[idx]);

                A[idx] = numDiv[A[idx]];

                if (A[idx] <= 2){
                    toBeRemoved.push_back(idx);
                }
            }

            for (auto idx: toBeRemoved)
                notConvergedYet.erase(idx);
        } else {
            printf("%lld\n", rsq(l, r));
        }
    }
}
