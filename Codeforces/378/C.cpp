#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, a[503], b[503];
    vector<pair<int, int> > segments;

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cin >> k;
    for (int i = 0; i < k; i++)
        cin >> b[i];

    for (int i = 0, segmentIdx = 0; i < n && segmentIdx < k; ) {
        int sum = 0;
        int j;
        for (j = i; j < n; j++) {
            sum += a[j];
            if (sum == b[segmentIdx]) {
                segments.push_back({i, j});
                segmentIdx += 1;
                break;
            }
        }

        i = j + 1;
    }

    if ((int) segments.size() != k || segments.back().second != n - 1) {
        cout << "NO\n";
        return 0;
    }

    int offset = 0;
    vector<pair<int, char> > moves;
    for (int segmentIdx = 0; segmentIdx < (int) segments.size(); segmentIdx++) {
        int l = segments[segmentIdx].first;
        int r = segments[segmentIdx].second;

        if (l == r)
            continue;

        //find the maximum
        int maxi = 0;
        for (int i = l; i <= r; i++)
            maxi = max(maxi, a[i]);

        int idx;

        //check if smaller weight exist to the left of maxi
        idx = -1;
        for (int i = l + 1; i <= r; i++) {
            if (a[i] == maxi && a[i - 1] < maxi) {
                idx = i;
                break;
            }
        }

        if (idx != -1) {
            for (int i = idx; i > l; i--)
                moves.push_back({segmentIdx + (i - l + 1), 'L'});

            for (int rep = 1; rep < (r - l + 1) - (idx - l + 1) + 1; rep++)
                moves.push_back({segmentIdx + 1, 'R'});

            continue;
        }

        //check if smaller weight exist to the right of maxi
        idx = -1;
        for (int i = r - 1; i >= l; i--) {
            if (a[i] == maxi && a[i + 1] < maxi) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            cout << "NO\n";
            return 0;
        }

        for (int rep = 1; rep < (r - l + 1) - (idx - l + 1) + 1; rep++)
            moves.push_back({segmentIdx + (idx - l + 1), 'R'});

        for (int i = idx; i > l; i--)
            moves.push_back({segmentIdx + (i - l + 1), 'L'});
    }

    cout << "YES\n";
    for (auto move: moves) {
        cout << move.first << " " << move.second << endl;
    }
}
