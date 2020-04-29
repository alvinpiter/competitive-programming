#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353
#define MAXN 200000

/*
Algorithm:
* For each robot i, find out the next robot j that will not be activated if robot i is activated. This can be done with segment tree and processing from the right most robot.
* dp[i] -> Number of possible subset from robot i until N. dp[i] = dp[i + 1] + dp[nxt[i]]
*/

int N, nxt[MAXN + 3], dp[MAXN + 3];
pair<int, int> robots[MAXN + 3];
int tree[4 * MAXN + 3];

void update(int node, int l, int r, int idx, int val) {
    if (r < idx || l > idx)
        return;

    if (l == r) {
        tree[node] = val;
        return;
    }

    int m = (l + r)/2;
    update(2 * node, l, m, idx, val);
    update(2 * node + 1, m + 1, r, idx, val);

    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

void update(int idx, int val) {
    update(1, 1, N, idx, val);
}

int query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return 0;

    if (l >= le && r <= ri)
        return tree[node];

    int m = (l + r)/2;
    return max(
        query(2 * node, l, m, le, ri),
        query(2 * node + 1, m + 1, r, le, ri)
    );
}

int query(int le, int ri) {
    return query(1, 1, N, le, ri);
}

int solve(int idx) {
    if (idx == N + 1)
        return 1;

    if (dp[idx] != -1)
        return dp[idx];

    int leave = solve(idx + 1);
    int take = solve(nxt[idx]);

    return dp[idx] = (leave + take)%MOD;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int X, D;
        scanf("%d%d", &X, &D);

        robots[i] = {X, D};
    }

    sort(robots + 1, robots + N + 1);

    memset(tree, 0, sizeof(tree));

    nxt[N] = N + 1;
    update(N, nxt[N]);

    for (int i = N - 1; i >= 1; i--) {
        int l = i + 1;

        int lo = 1, hi = N, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (robots[mid].first >= robots[i].first + robots[i].second)
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        int r = hi;

        if (l <= r) {
            nxt[i] = query(l, r);
        } else {
            nxt[i] = l;
        }

        update(i, nxt[i]);
    }

    memset(dp, -1, sizeof(dp));

    printf("%d\n", solve(1));
}
