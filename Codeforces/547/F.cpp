#include<bits/stdc++.h>
using namespace std;
#define MAXN 1500

int n, a[MAXN + 3];
map<int, vector<pair<int, int> > > segments;

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    //generate segments
    for (int r = 1; r <= n; r++) {
        int sum = 0;
        for (int l = r; l >= 1; l--) {
            sum += a[l];
            segments[sum].push_back({l, r});
        }
    }

    vector<pair<int, int> > answer;
    for (auto seg: segments) {
        vector<pair<int, int> > segs = seg.second;

        int last = 0;
        vector<pair<int, int> > temp;

        for (int i = 0; i < (int) segs.size(); i++) {
            if (segs[i].first > last) {
                temp.push_back(segs[i]);
                last = segs[i].second;
            }
        }

        if (temp.size() > answer.size())
            answer = temp;
    }

    cout << answer.size() << endl;
    for (auto a: answer) {
        cout << a.first << " " << a.second << endl;
    }
}
