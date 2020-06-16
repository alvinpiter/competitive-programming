#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e18
#define MAXN 200000

/*
Imagine we would like to go from a to b by using a teleport with values (x, y, t).
The time taken if we use the teleport is |x - a| + |y - b| + t. We would like to minimize this value.

There are 4 cases to consider:
* x >= a && y >= b
* x >= a && y < b
* x < a && y >= b
* x < a && y < b

Let's dig in on the first case, the other three cases are similar. In the first case, the formula can
be written as:
(x - a) + (y - b) + t
(x + y + t) - (a + b)

We can answer the query in offline manner. For a given (a, b), make sure we already included
all (x, y, t) whose x >= a into our "data structure" (here we use segment tree). The (x, y, t) will
be keyed by y and the value will be x + y + t. We then can get the minimum time by querying our data
structure for value whose key is >= b.

The formulas for the other 3 cases:
* (x - a) + (b - y) + t = (x - y + t) - (a - b)
* (a - x) + (y - b) + t = (-x + y + t) + (a - b)
* (a - x) + (b - y) + t = (-x - y + t) + (a + b)
*/

struct Query {
    int a, b, index;
    Query(int _a, int _b, int _index): a(_a), b(_b), index(_index) {}
    bool operator<(Query other) const {
        return a < other.a;
    }
};

struct Slingshot {
    int x, y, t;
    Slingshot(int _x, int _y, int _t): x(_x), y(_y), t(_t) {}
    bool operator<(Slingshot other) const {
        return x < other.x;
    }
};

class SegmentTree {
private:
    int N;
    LL tree[4 * MAXN + 3];

    void update(int node, int l, int r, int idx, LL val) {
        if (r < idx || l > idx)
            return;

        if (l == r) {
            tree[node] = val;
            return;
        }

        int m = (l + r)/2;
        update(2 * node, l, m, idx, val);
        update(2 * node + 1, m + 1, r, idx, val);

        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }

    LL query(int node, int l, int r, int le, int ri) {
        if (r < le || l > ri)
            return INF;

        if (l >= le && r <= ri)
            return tree[node];

        int m = (l + r)/2;
        return min(
            query(2 * node, l, m, le, ri),
            query(2 * node + 1, m + 1, r, le, ri)
        );
    }
public:
    SegmentTree(int n) {
        N = n;
        for (int i = 1; i <= 4 * N; i++)
            tree[i] = INF;
    }

    void update(int idx, LL val) {
        update(1, 1, N, idx, val);
    }

    LL query(int l, int r) {
        return query(1, 1, N, l, r);
    }

    void reset() {
        for (int i = 1; i <= 4 * N; i++)
            tree[i] = INF;
    }
};

int N, M;
LL ans[MAXN + 3];
vector<Slingshot> slingshots; //{x, {y, t}}
vector<Query> queries;
vector<int> uniqY;

int normalizeY(int y) {
    return (lower_bound(uniqY.begin(), uniqY.end(), y) - uniqY.begin()) + 1;
}

int main() {
    freopen("slingshot.in", "r", stdin);
    freopen("slingshot.out", "w", stdout);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int x, y, t;
        cin >> x >> y >> t;

        slingshots.push_back(Slingshot(x, y, t));
        uniqY.push_back(y);
    }

    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;

        queries.push_back(Query(a, b, i));
        uniqY.push_back(b);
    }

    sort(uniqY.begin(), uniqY.end());
    uniqY.resize(distance(uniqY.begin(), unique(uniqY.begin(), uniqY.end())));

    for (int i = 0; i < M; i++)
        ans[i] = INF;

    sort(slingshots.begin(), slingshots.end());
    sort(queries.begin(), queries.end());

    //variables for line sweep
    SegmentTree below = SegmentTree(uniqY.size());
    SegmentTree above = SegmentTree(uniqY.size());
    int ptr;

    //scan left to right
    ptr = 0;
    for (int i = 0; i < M; i++) {
        while (ptr < N && queries[i].a >= slingshots[ptr].x) {
            LL x = slingshots[ptr].x, y = slingshots[ptr].y, t = slingshots[ptr].t;
            int normalizedY = normalizeY(y);

            above.update(normalizedY, -x + y + t);
            below.update(normalizedY, -x - y + t);

            ptr += 1;
        }

        /*
        Case x <= a && y > b -> (a - x) + (y - b) + t = (-x + y + t) + (a - b)
        Case x <= a && y <= b -> (a - x) + (b - y) + t = (-x - y + t) + (a + b)
        */

        int a = queries[i].a, b = queries[i].b, idx = queries[i].index;
        ans[idx] = min(ans[idx], below.query(1, normalizeY(b)) + (a + b));
        ans[idx] = min(ans[idx], above.query(normalizeY(b), uniqY.size()) + (LL) (a - b));
    }

    //scan right to left
    below.reset();
    above.reset();

    ptr = N - 1;
    for (int i = M - 1; i >= 0; i--) {
        while (ptr >= 0 && queries[i].a <= slingshots[ptr].x) {
            LL x = slingshots[ptr].x, y = slingshots[ptr].y, t = slingshots[ptr].t;
            int normalizedY = normalizeY(y);

            above.update(normalizedY, x + y + t);
            below.update(normalizedY, x - y + t);

            ptr -= 1;
        }

        /*
        Case x > a && y > b -> (x - a) + (y - b) + t = (x + y + t) - (a + b)
        Case x > a && y <= b -> (x - a) + (b - y) + t = (x - y + t) - (a - b)
        */

        int a = queries[i].a, b = queries[i].b, idx = queries[i].index;
        ans[idx] = min(ans[idx], below.query(1, normalizeY(b)) - (a - b));
        ans[idx] = min(ans[idx], above.query(normalizeY(b), uniqY.size()) - (a + b));
    }

    //If it is better to go directly (no need slingshot)
    for (int i = 0; i < M; i++) {
        int a = queries[i].a, b = queries[i].b, idx = queries[i].index;
        ans[idx] = min(ans[idx], (LL) abs(a - b));
    }

    for (int i = 0; i < M; i++)
        cout << ans[i] << endl;
}
