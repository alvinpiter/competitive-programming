#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int X, N, p, answer[MAXN + 3];
multiset<int> pos;
multiset<int> segmentLengths;

int main() {
    cin >> X >> N;

    pos.insert(0);
    pos.insert(X);
    segmentLengths.insert(X);

    for (int i = 1; i <= N; i++) {
        cin >> p;
        int right = *(pos.lower_bound(p));
        int left = *(--pos.lower_bound(p));

        segmentLengths.erase(segmentLengths.find(right - left));
        segmentLengths.insert(p - left);
        segmentLengths.insert(right - p);

        pos.insert(p);

        answer[i] = *(segmentLengths.rbegin());
    }

    for (int i = 1; i <= N; i++) {
        if (i > 1)
            cout << " ";

        cout << answer[i];
    }
    cout << endl;
}
