#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, X[MAXN + 3], P, tree[4 * MAXN + 3];

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

//Find index i such that sum of numbers at index 1..i is k
int query(int node, int l, int r, int k) {
    if (l == r)
        return l;

    int m = (l + r)/2;
    if (k <= tree[2 * node])
        return query(2 * node, l, m, k);
    else
        return query(2 * node + 1, m + 1, r, k - tree[2 * node]);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &X[i]);

    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= N; i++)
        update(1, 1, N, i, 1);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &P);

        int idx = query(1, 1, N, P);
        printf("%d", X[idx]);
        if (i == N)
            printf("\n");
        else
            printf(" ");

        update(1, 1, N, idx, -1);
    }
}
