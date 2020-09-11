#include<bits/stdc++.h>
using namespace std;
#define MAXN 50000
#define MAXV 1000010

/*
Line sweep + BIT. Maintain a set of segments which denote active rectangles height.
If there is a segment that encloses the new segment, the the new rectangle is enclosed.

It is hard to find whether there is a segment that encloses the new segment, but it is
easy to find how many segment that ends before or starts after the new segment. We can
do it by maintaining 2 BITs. One for keeping track where a segment starts, one for keeping
track where a segment ends.
*/

struct Event {
    int x, y1, y2, type, index;
    Event(int _x, int _y1, int _y2, int _type, int _index): x(_x), y1(_y1), y2(_y2), type(_type), index(_index) {}
};

bool cmp(Event a, Event b) {
    if (a.x != b.x)
        return a.x < b.x;
    else
        return a.type < b.type;
}

int N;
bool isEnclosed[MAXN + 3];
vector<Event> events;

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

int main() {
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        //y values are normalized to be in range 1..1000001
        events.push_back(Event(x1, y1 + 1, y2 + 1, +1, i));
        events.push_back(Event(x2, y1 + 1, y2 + 1, -1, i));
    }

    sort(events.begin(), events.end(), cmp);

    memset(isEnclosed, false, sizeof(isEnclosed));

    int bitTop[MAXV + 3], bitBottom[MAXV + 3];

    memset(bitTop, 0, sizeof(bitTop));
    memset(bitBottom, 0, sizeof(bitBottom));

    for (int i = 0; i < events.size(); ) {
        int j;
        for (j = i; j < events.size() && events[j].x == events[i].x; j++) {
            int y1 = events[j].y1;
            int y2 = events[j].y2;

            if (events[j].type == -1) {
                update(bitBottom, y1, -1);
                update(bitTop, y2, -1);
            } else {
                int all = query(bitBottom, MAXV);
                int endingBeforeY1 = query(bitTop, y1);
                int startingAfterY2 = query(bitBottom, MAXV) - query(bitBottom, y2 - 1);

                if (all != endingBeforeY1 + startingAfterY2)
                    isEnclosed[events[j].index] = true;

                update(bitBottom, y1, 1);
                update(bitTop, y2, 1);
            }
        }

        i = j;
    }

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        if (!isEnclosed[i])
            answer += 1;
    }

    cout << answer << endl;
}
