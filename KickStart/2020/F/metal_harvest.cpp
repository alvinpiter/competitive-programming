#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

int T, N, K, answer;
vector<pair<int, int> > segments;

int ceil(int a, int b) {
    if (a % b == 0) {
        return a/b;
    } else {
        return a/b + 1;
    }
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> K;

        segments.clear();
        for (int i = 0; i < N; i++) {
            int l, r;
            cin >> l >> r;

            segments.push_back(make_pair(l, r));
        }

        sort(segments.begin(), segments.end());

        answer = 0;
        int endTime = segments[0].first;

        for (int i = 0; i < N; ) {
            if (segments[i].second <= endTime) {
                i++;
                continue;
            }

            if (endTime <= segments[i].first) {
                int need = ceil(segments[i].second - segments[i].first, K);

                answer += need;
                endTime = segments[i].first + K * need;
            } else {
                int need = ceil(segments[i].second - endTime, K);

                answer += need;
                endTime += K * need;
            }
        }

        cout << "Case #" << cases << ": " << answer << endl;
    }
}
