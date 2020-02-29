#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

string s;
int q, n, tree[4 * MAXN + 3];

int mask(char c) {
    int idx = (c - 'a');
    return (1 << idx);
}

int countOnBit(int msk) {
    int result = 0;
    for (int i = 0; i < 26; i++) {
        if (msk & (1 << i))
            result += 1;
    }
    return result;
}

void update(int node, int l, int r, int pos, int val) {
    if (r < pos || l > pos)
        return;

    if (l == r) {
        tree[node] = val;
        return;
    }

    int m = (l + r)/2;
    update(2 * node, l, m, pos, val);
    update(2 * node + 1, m + 1, r, pos, val);

    tree[node] = tree[2 * node] | tree[2 * node + 1];
}

int query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return 0;

    if (l >= le && r <= ri)
        return tree[node];

    int m = (l + r)/2;
    return query(2 * node, l, m, le, ri) | query(2 * node + 1, m + 1, r, le, ri);
}

int main() {
    cin >> s;
    n = s.length();

    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= n; i++)
        update(1, 1, n, i, mask(s[i - 1]));

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int typ, pos, l, r;
        char c[2];

        scanf("%d", &typ);
        if (typ == 1) {
            scanf("%d%s", &pos, c);
            update(1, 1, n, pos, mask(c[0]));
        } else {
            scanf("%d%d", &l, &r);
            int result = query(1, 1, n, l, r);
            printf("%d\n", countOnBit(result));
        }
    }
}
