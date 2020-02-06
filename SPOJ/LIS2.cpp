#include<bits/stdc++.h>
using namespace std;
#define INF 2000000000
#define MAXN 100000

class StaircaseDS {
private:
    set<pair<int, int> > sets;

public:
    //Check if there is a point in the set that is located strictly inside p's third quadrant.
    bool check(pair<int, int> p) {
        set<pair<int, int> >::iterator lb = sets.lower_bound(make_pair(p.first, -INF));
        if (lb == sets.begin()) {
            return false;
        } else {
            return -((--lb)->second) < p.second;
        }
    }

    //Insert p to the set, possibly removing some obsolete points
    void insert(pair<int, int> p) {
        if (check(p) == true)
            return;

        while (true) {
            set<pair<int, int> >::iterator lb = sets.lower_bound(make_pair(p.first, -INF));

            if (lb == sets.end() || -(lb->second) < p.second)
                break;
            else {
                sets.erase(lb);
            }
        }

        sets.insert(make_pair(p.first, -p.second));
    }

    void print() {
        cout << "Current set:\n";
        for (set<pair<int, int> >::iterator it = sets.begin(); it != sets.end(); ++it) {
            cout << it->first << " " << -(it->second) << endl;
        }
    }
};

void staircaseTest() {
    StaircaseDS stair;

    while (true) {
        int t, x, y;
        cin >> t >> x >> y;

        if (t == 1) {
            cout << stair.check(make_pair(x, y)) << endl;
        } else {
            stair.insert(make_pair(x, y));
        }

        stair.print();
        cout << endl;
    }
}

int main() {
    int N, LIS;
    StaircaseDS len[MAXN + 3];

    cin >> N;

    LIS = 0;
    for (int i = 1; i <= N; i++) {
        pair<int, int> p;
        scanf("%d%d", &p.first, &p.second);

        int lo = 1, hi = LIS, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;

            if (len[mid].check(p))
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        if (lo == LIS + 1) {
            LIS += 1;
        }

        len[lo].insert(p);
    }

    cout << LIS << endl;
}
