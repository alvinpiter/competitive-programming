#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

int n, q, tree[4 * MAXN + 3];

void update(int node, int l, int r, int idx, int val) {
    if (r < idx || l > idx)
        return;

    if (l == r) {
        tree[node] += val;
        return;
    }

    int m = (l + r)/2;
    update(2 * node, l, m, idx, val);
    update(2 * node + 1, m + 1, r, idx, val);

    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

void update(int idx, int val) {
    update(1, 1, n, idx, val);
}

int getKth(int node, int l, int r, int k) {
    if (k > tree[node])
        return 0;

    if (l == r)
        return l;

    int m = (l + r)/2;
    if (k <= tree[2 * node])
        return getKth(2 * node, l, m, k);
    else
        return getKth(2 * node + 1, m + 1, r, k - tree[2 * node]);
}

int getKth(int k) {
    return getKth(1, 1, n, k);
}

int main() {
    scanf("%d%d", &n, &q);

    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        update(a, 1);
    }

    for (int i = 1; i <= q; i++) {
        int k;
        scanf("%d", &k);

        if (k > 0) {
            update(k, 1);
        } else {
            int kth = getKth(abs(k));
            update(kth, -1);
        }
    }

    printf("%d\n", getKth(1));
}
