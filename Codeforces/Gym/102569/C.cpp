#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

/*
Alternative formula for Manhattan distance between two points:
max(|(x1 + y1) - (x2 + y2)|, |(x1 - y1) - (x2 - y2)|)

The formula above is corollary of |a| + |b| = max(|a + b|, |a - b|). The proof can be done in two ways:
* proof by cases
* proof by algebra

Convert the point's coordinate from (x, y) to (x + y, x - y).

Now try to guess the answer, let's say the answer is d.
If the answer is d, then the number of pair of points with distance < d must be smaller than k.

To count the number of pair of points with distance < d, can be done with line sweep and Fenwick tree.
*/

int n;
LL k;
vector<pair<int, int> > points;

vector<int> uniqY;
int numY, bit[MAXN + 3];

void update(int idx, int val) {
    while (idx <= numY) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int rsq(int l, int r) {
    return query(r) - query(l - 1);
}

int getCompressedIndex(int y) {
    return (lower_bound(uniqY.begin(), uniqY.end(), y) - uniqY.begin()) + 1;
}

int main() {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        points.push_back({x + y, x - y});
        uniqY.push_back(x - y);
    }

    sort(points.begin(), points.end());

    sort(uniqY.begin(), uniqY.end());
    uniqY.resize(distance(uniqY.begin(), unique(uniqY.begin(), uniqY.end())));

    numY = (int) uniqY.size();

    int lo = 0, hi = 4*100000000, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        memset(bit, 0, sizeof(bit));

        LL cnt = 0; //how many pairs of points with manhattan distance less than mid
        int ptrLeft = 0, ptrRight = -1;

        for (int i = 0; i < n; i++) {
            //remove obsolete points
            while (points[i].first - points[ptrLeft].first >= mid) {
                int y = getCompressedIndex(points[ptrLeft].second);
                update(y, -1);
                ptrLeft += 1;
            }

            //add new points
            while (ptrRight + 1 < n && points[ptrRight + 1].first - points[i].first < mid) {
                int y = getCompressedIndex(points[ptrRight + 1].second);
                update(y, 1);
                ptrRight += 1;
            }

            //query
            int lb = (lower_bound(uniqY.begin(), uniqY.end(), points[i].second - (mid - 1)) - uniqY.begin()) + 1;
            int ub = (upper_bound(uniqY.begin(), uniqY.end(), points[i].second + (mid - 1)) - uniqY.begin()) + 1;

            cnt += ((LL) rsq(lb, ub - 1) - 1);
        }

        cnt /= 2;

        if (cnt >= k)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    printf("%d\n", hi);
}
