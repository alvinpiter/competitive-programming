#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100001
#define DEBUG true

/*
First of all, let's increase the height of hairs by 1. This is to make sure the minimal height is 1, instead of 0.

We can solve the problem by line sweep algorithm. We sweep h from 1 to N.
When we are currently at h, we include all hair whose high is h - 1.
Each of those hair will contribute as many as number of hairs to its left that is higher.
*/

int N, A[MAXN + 3], bit[MAXN + 3];
LL inversion, cntHigher[MAXN + 3]; //cntHigher[h] -> how many hairs higher than h to the left of all hairs with height h

void update(int idx, int val) {
    while (idx <= MAXN) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int rsq(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);

    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i] += 1; //make the minimal height equals to 1 instead of 0.
    }

    memset(cntHigher, 0, sizeof(cntHigher));
    memset(bit, 0, sizeof(bit));

    for (int i = 1; i <= N; i++) {
        cntHigher[A[i]] += rsq(A[i] + 1, MAXN);
        update(A[i], 1);
    }

    inversion = 0;
    for (int h = 1; h <= N; h++) {
        inversion += cntHigher[h - 1];
        printf("%lld\n", inversion);
    }
}
