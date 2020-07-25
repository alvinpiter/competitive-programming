#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, M, H[MAXN + 3];
int tree[4 * MAXN + 3];

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

    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

//Find the first hotel that has at least sz empty rooms
int find(int node, int l, int r, int sz) {
    if (l == r) {
        if (tree[node] < sz)
            return 0;
        else
            return l;
    }

    int m = (l + r)/2;
    if (tree[2 * node] >= sz)
        return find(2 * node, l, m, sz);
    else
        return find(2 * node + 1, m + 1, r, sz);
}

int main() {
    scanf("%d%d", &N, &M);

    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &H[i]);
        update(1, 1, N, i, H[i]);
    }

    for (int i = 1; i <= M; i++) {
        int R;
        scanf("%d", &R);

        int idx = find(1, 1, N, R);
        printf("%d", idx);
        if (i == M)
            printf("\n");
        else
            printf(" ");

        if (idx != 0) {
            update(1, 1, N, idx, -R);
        }
    }
}
