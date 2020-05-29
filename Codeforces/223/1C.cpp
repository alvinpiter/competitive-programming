#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000
#define Node pair<int, int>

string s;
int n, q;
Node tree[4 * MAXN + 3]; //{number of unmatched closing, number of unmatched opening}

Node merge(Node a, Node b) {
    int cancels = min(a.second, b.first);
    return make_pair(
        a.first + (b.first - cancels),
        b.second + (a.second - cancels)
    );
}

void build(int node, int l, int r) {
    if (l == r) {
        int open = (s[l - 1] == '(' ? 1 : 0);
        int close = (s[l - 1] == ')' ? 1 : 0);
        tree[node] = {close, open};
        return;
    }

    int m = (l + r)/2;
    build(2 * node, l, m);
    build(2 * node + 1, m + 1, r);

    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

Node query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return make_pair(0, 0);

    if (l >= le && r <= ri)
        return tree[node];

    int m = (l + r)/2;
    return merge(
        query(2 * node, l, m, le, ri),
        query(2 * node + 1, m + 1, r, le, ri)
    );
}

int main() {
    cin >> s;

    n = (int) s.length();

    build(1, 1, n);

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;

        Node result = query(1, 1, n, l, r);
        cout << (r - l + 1) - (result.first + result.second) << endl;
    }
}
