#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXV 1000000

/*
Let's fix a vertical line and find the best horizontal line.
For a given vertical and horizontal line, the value of M will be determined by maximum of:
* aboveLeft -> Number of points to the left of vertical line and above horizontal line.
* aboveRight
* belowLeft
* belowRight

If max(aboveLeft, aboveRight) > max(belowLeft, belowRight), then it might be better to look
for best horizontal line above. Otherwise, we go below. This can be done with binary search.

To maintain set of points to the left and right of vertical line, we can use 2 BIT.
*/

int bitLeft[MAXV + 3], bitRight[MAXV + 3];

void update(int bit[], int idx, int val) {
    while (idx <= MAXV) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int bit[], int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int N, answer;
vector<int> ys[MAXV + 3]; //ys[x] -> y coordinate of cows at x

int main() {
    freopen("balancing.in", "r", stdin);
    freopen("balancing.out", "w", stdout);

    cin >> N;

    memset(bitLeft, 0, sizeof(bitLeft));
    memset(bitRight, 0, sizeof(bitRight));

    for (int i = 1; i <= N; i++) {
        int x, y;
        cin >> x >> y;

        ys[x].push_back(y);
        update(bitRight, y, 1);
    }

    answer = N;
    for (int x = 0; x <= MAXV; x += 2) {
        //find best horizontal cut
        int lo = 0, hi = MAXV/2, mid;
        while (hi >= lo) {
            // cout << lo << " " << hi << endl;
            mid = (lo + hi)/2;

            int y = 2 * mid;

            int aboveLeft = query(bitLeft, MAXV) - query(bitLeft, y);
            int aboveRight = query(bitRight, MAXV) - query(bitRight, y);
            int belowLeft = query(bitLeft, y);
            int belowRight = query(bitRight, y);

            int maxAbove = max(aboveLeft, aboveRight);
            int maxBelow = max(belowLeft, belowRight);

            answer = min(answer, max(maxAbove, maxBelow));

            if (maxAbove >= maxBelow)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        for (auto y: ys[x + 1]) {
            update(bitLeft, y, 1);
            update(bitRight, y, -1);
        }
    }

    cout << answer << endl;
}
