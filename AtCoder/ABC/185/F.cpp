#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXLG 30
#define MAXN 300000

int N, Q, A[MAXN + 3], tree[4 * MAXN + 2];

void update(int node, int l, int r, int idx, int val) {
    if (idx < l || idx > r) {
        return;
    }

    if (l == r) {
        tree[node] = val;
        return;
    }

    int m = (l + r)/2;
    update(2 * node, l, m, idx, val);
    update(2 * node + 1, m + 1, r, idx, val);

    tree[node] = tree[2 * node] ^ tree[2 * node + 1];
}

int query(int node, int l, int r, int le, int ri) {
    if (ri < l || le > r) {
        return false;
    }

    if (l >= le && r <= ri) {
        return tree[node];
    }

    int m = (l + r)/2;
    int lefty = query(2 * node, l, m, le, ri);
    int righty = query(2 * node + 1, m + 1, r, le, ri);

    return lefty ^ righty;
}

int main() {
    scanf("%d%d", &N, &Q);

    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        update(1, 1, N, i, A[i]);
    }

    for (int q = 1; q <= Q; q++) {
        int T, X, Y;

        scanf("%d%d%d", &T, &X, &Y);
        if (T == 1) {
            A[X] = A[X]^Y;
            update(1, 1, N, X, A[X]);
        } else {
            printf("%d\n", query(1, 1, N, X, Y));
        }
    }
}
