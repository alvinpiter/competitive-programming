#include<bits/stdc++.h>
using namespace std;

int main() {
    int t, n, a, cnt[3];

    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n;

        memset(cnt, 0, sizeof(cnt));
        for (int i = 1; i <= n; i++) {
            cin >> a;
            cnt[a%3] += 1;
        }

        int answer = cnt[0];
        int takeOneTwo = min(cnt[1], cnt[2]);

        answer += takeOneTwo;
        answer += (cnt[1] - takeOneTwo)/3;
        answer += (cnt[2] - takeOneTwo)/3;

        cout << answer << endl;
    }
}
