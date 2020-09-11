#include<bits/stdc++.h>
using namespace std;

/*
Maintain a window with size k - 1. In side the window, store the y coordinate of
the points. Whenever a new point incoming, check if it overlaps with other points.
*/

int N, K;
vector<pair<int, int> > points;

int main() {
    freopen("squares.in", "r", stdin);
    freopen("squares.out", "w", stdout);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;

        points.push_back({x, y});
    }

    sort(points.begin(), points.end());

    set<pair<int, int> > window; //{y, index}
    pair<int, int> overlapIndices = {-1, -1};

    int ptr = 0;
    for (int i = 0; i < N; i++) {
        //remove out-of-range points
        while (points[i].first - points[ptr].first > K - 1) {
            window.erase({points[ptr].second, ptr});
            ptr += 1;
        }

        window.insert({points[i].second, i});

        auto nxt = window.find({points[i].second, i});
        auto prv = nxt;

        if (++nxt != window.end() && nxt->first - points[i].second < K) {
            if (overlapIndices.first != -1) {
                cout << -1 << endl;
                return 0;
            }

            overlapIndices = {nxt->second, i};
        }

        if (prv-- != window.begin() && points[i].second - prv->first < K) {
            if (overlapIndices.first != -1) {
                cout << -1 << endl;
                return 0;
            }

            overlapIndices = {prv->second, i};
        }
    }

    if (overlapIndices.first == -1)
        cout << 0 << endl;
    else {
        int i1 = overlapIndices.first;
        int i2 = overlapIndices.second;

        int dx = K - abs(points[i2].first - points[i1].first);
        int dy = K - abs(points[i2].second - points[i1].second);

        long long int ans = (long long int) dx * dy;

        cout << ans << endl;
    }
}
