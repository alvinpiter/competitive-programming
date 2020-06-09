#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int N, M;
vector<pair<LL, LL> > segments;

//Can we put N cows such that each of them are at least d apart
bool possible(LL d) {
    LL currentPos = segments[0].first;
    int cnt = 0;

    while (true) {
        cnt += 1;
        if (cnt >= N)
            return true;

        //find next segment
        int lo = 0, hi = M - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (segments[mid].first < currentPos + d)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        if (segments[hi].second < currentPos + d) {
            if (hi == M - 1)
                break;
            else
                currentPos = segments[hi + 1].first;
        } else {
            currentPos += d;
        }
    }

    return false;
}

int main() {
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        LL l, r;
        cin >> l >> r;

        segments.push_back({l, r});
    }

    sort(segments.begin(), segments.end());

    LL lo = 0, hi = 1e18, mid;

    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (possible(mid))
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    cout << hi << endl;
}
