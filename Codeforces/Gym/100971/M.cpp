#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 200000

/*
mini[j] -> minimum i such that substring i..j contains exactly k different characters
maxi[j] -> maximum i such that substring i..j contains exactly k different characters
*/

int k, n, dp[MAXN + 3];
int mini[MAXN + 3], maxi[MAXN + 3], cnt[26], cntUniq;
int tree[4 * MAXN + 3];
string s;

void add(int charIdx) {
    if (cnt[charIdx] == 0)
        cntUniq += 1;

    cnt[charIdx] += 1;
}

void remove(int charIdx) {
    if (cnt[charIdx] == 1)
        cntUniq -= 1;

    cnt[charIdx] -= 1;
}

void updateSegTree(int node, int l, int r, int idx, int val) {
    if (r < idx || l > idx)
        return;

    if (l == r) {
        tree[node] = val;
        return;
    }

    int m = (l + r)/2;
    updateSegTree(2 * node, l, m, idx, val);
    updateSegTree(2 * node + 1, m + 1, r, idx, val);

    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int querySegTree(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return INF;

    if (l >= le && r <= ri)
        return tree[node];

    int m = (l + r)/2;
    return min(
        querySegTree(2 * node, l, m, le, ri),
        querySegTree(2 * node + 1, m + 1, r, le, ri)
    );
}

void initializeMini() {
    memset(cnt, 0, sizeof(cnt));
    cntUniq = 0;
    int ptr = 1;

    for (int i = 1; i <= n; i++) {
        add(s[i - 1] - 'a');

        mini[i] = -1;

        while (cntUniq > k) {
            remove(s[ptr - 1] - 'a');
            ptr += 1;
        }

        if (cntUniq == k)
            mini[i] = ptr;
    }
}

void initializeMaxi() {
    memset(cnt, 0, sizeof(cnt));
    cntUniq = 0;
    int ptr = 1;

    for (int i = 1; i <= n; i++) {
        add(s[i - 1] - 'a');

        maxi[i] = -1;

        while (cntUniq >= k) {
            remove(s[ptr - 1] - 'a');
            ptr += 1;
        }

        if (ptr != 1 && cntUniq == k - 1)
            maxi[i] = ptr - 1;
    }
}

int main() {
    cin >> k >> s;

    n = (int) s.length();

    initializeMini();
    initializeMaxi();

    for (int i = 1; i <= 4 * n; i++)
        tree[i] = INF;

    for (int i = 1; i <= n; i++) {
        if (mini[i] == -1) {
            dp[i] = INF;
        } else {
            if (mini[i] == 1)
                dp[i] = 1;
            else {
                int l = mini[i] - 1;
                int r = maxi[i] - 1;

                dp[i] = 1 + querySegTree(1, 1, n, l, r);
            }
        }

        updateSegTree(1, 1, n, i, dp[i]);

        if (dp[i] < INF)
            printf("%d ", dp[i]);
        else
            printf("-1 ");
    }

    printf("\n");
}
