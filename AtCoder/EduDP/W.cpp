#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e18
#define MAXN 200000

/*
Define dp[i] as maximum possible score out of the first i characters of the string, given the
i-th character is a 1.

dp[i] = max(dp[j] + (sum of value of all segments whose l is j < l <= i and whose r is r >= i))

Naive iteration will yield O(N^2) complexity, hence we need to use a segment tree and line sweep.
The i-th element in the segment tree will contain the value dp[i] + (sum of value of desired segments).
In order for our segment tree always maintain correct value, we have to consider two cases:
* Whenever we encounter a beginning of a segment, we will update our segment tree at index 0..l[i] - 1 by +a
* Whenever we encounter an ending of a segment, we will update our segment tree at index 0..l[i] - 1 by -a.
*/

LL tree[4 * MAXN + 3], lazy[4 * MAXN + 3];

LL evaluate(int node) {
    return tree[node] + lazy[node];
}

void pushDown(int node) {
    lazy[2 * node] += lazy[node];
    lazy[2 * node + 1] += lazy[node];
    lazy[node] = 0;
}

void pullUp(int node) {
    tree[node] = max(evaluate(2 * node), evaluate(2 * node + 1));
}

void update(int node, int l, int r, int le, int ri, LL val) {
    if (r < le || l > ri)
        return;

    if (l >= le && r <= ri) {
        lazy[node] += val;
        return;
    }

    pushDown(node);

    int m = (l + r)/2;
    update(2 * node, l, m, le, ri, val);
    update(2 * node + 1, m + 1, r, le, ri, val);

    pullUp(node);
}

LL query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return -INF;

    if (l >= le && r <= ri)
        return evaluate(node);

    pushDown(node);

    int m = (l + r)/2;
    LL leftResult = query(2 * node, l, m, le, ri);
    LL rightResult = query(2 * node + 1, m + 1, r, le, ri);

    pullUp(node);

    return max(leftResult, rightResult);
}

int N, M, l[MAXN + 3], r[MAXN + 3], a[MAXN + 3];
vector<pair<int, int> > events[MAXN + 3]; //{type, idx}
LL dp[MAXN + 3], answer;

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        scanf("%d%d%d", &l[i], &r[i], &a[i]);

        events[l[i]].push_back({1, i});
        events[r[i] + 1].push_back({-1, i});
    }

    //Init segment tree
    for (int i = 0; i <= 4 * N; i++) {
        tree[i] = 0;
        lazy[i] = 0;
    }

    dp[0] = 0;
    update(1, 0, N, 0, 0, dp[0]);

    answer = 0;
    for (int i = 1; i <= N; i++) {
        //process all events at index i
        for (auto e: events[i]) {
            int type = e.first, idx = e.second;
            if (type == -1)
                update(1, 0, N, 0, l[idx] - 1, -a[idx]);
            else
                update(1, 0, N, 0, l[idx] - 1, +a[idx]);
        }

        dp[i] = query(1, 0, N, 0, i - 1);
        update(1, 0, N, i, i, dp[i]);

        answer = max(answer, dp[i]);
    }

    printf("%lld\n", answer);
}
