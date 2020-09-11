#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, Q, X[MAXN + 3];
LL BIT[MAXN + 3];

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

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &X[i]);
    }

    memset(BIT, 0, sizeof(BIT));
    for (int i = 1; i <= Q; i++) {
        int t;
        scanf("%d", &t);
        if (t == 1) {
            int a, b, u;
            scanf("%d%d%d", &a, &b, &u);
            update(a, u);
            update(b + 1, -u);
        } else {
            int k;
            scanf("%d", &k);
            printf("%lld\n", (LL) X[k] + query(k));
        }
    }
}
