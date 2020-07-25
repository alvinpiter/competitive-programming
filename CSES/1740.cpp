#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXX 2000001

/*
Loop over vertical lines starting from the left most one.
Maintain a set of horizontal lines whose x-range covers current vertical
line's x. The number of intersections on current vertical lines equal to
number of active horizontal lines whose y is in current vertical line's
y-range.
*/

int N, BIT[MAXX + 3];
vector<pair<int, pair<int, int> > > vLines;
vector<pair<int, int> > xEvents;

int update(int idx, int val) {
    while (idx <= MAXX) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int rsq(int a, int b) {
    return query(b) - query(a - 1);
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

        x1 += 1000001;
        y1 += 1000001;
        x2 += 1000001;
        y2 += 1000001;

        if (x1 == x2) {
            //It is a vertical line
            vLines.push_back({x1, {y1, y2}});
        } else {
            //It is a horizontal line
            xEvents.push_back({x1, y1});
            xEvents.push_back({x2 + 1, -y1});
        }
    }

    sort(vLines.begin(), vLines.end());
    sort(xEvents.begin(), xEvents.end());

    memset(BIT, 0, sizeof(BIT));

    LL answer = 0;
    int ptr = 0;

    for (int i = 0; i < (int) vLines.size(); i++) {
        int x = vLines[i].first;
        while (ptr < (int) xEvents.size() && xEvents[ptr].first <= x) {
            int y = xEvents[ptr].second;
            if (y > 0)
                update(y, 1);
            else
                update(-y, -1);

            ptr += 1;
        }

        int numIntersections = rsq(vLines[i].second.first, vLines[i].second.second);
        answer += numIntersections;
    }

    printf("%lld\n", answer);
}
