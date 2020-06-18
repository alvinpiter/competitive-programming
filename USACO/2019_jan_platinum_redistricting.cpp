#include<bits/stdc++.h>
using namespace std;
#define MAXN 300000

/*
Replace every H to be -1, and every G to be 1.
We want to minimize number of segment with length at most K whose sum is positive.

Define dp[j] = min number of segment in the first j numbers that fulfills the constraint.

dp[j] is either:
* dp[i] + 1, if prefix[j] - prefix[i] >= 0 and j - K <= i <= j - 1
* dp[i], prefix[j] - prefix[i] < 0 and j - K <= i <= j - 1

Define M as min(dp[i]), for j - K <= i <= j - 1.
The key observation is that dp[j] is either M or M + 1.
So we need to check if dp[j] is M. If it's not possible, then it must be M + 1.
*/

int N, K, ps[MAXN + 3], dp[MAXN + 3];

int main() {
    freopen("redistricting.in", "r", stdin);
    freopen("redistricting.out", "w", stdout);

    cin >> N >> K;

    ps[0] = 0;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        ps[i] = ps[i - 1] + (c == 'H' ? -1 : +1);
    }

    multiset<pair<int, int> > activePsDp; //{ps[i], dp[i]}
    multiset<int> activeDp;

    dp[0] = 0;
    activePsDp.insert({ps[0], dp[0]});
    activeDp.insert(dp[0]);

    int ptr = 0;
    for (int j = 1; j <= N; j++) {
        if (ptr < j - K) {
            activePsDp.erase(activePsDp.find({ps[ptr], dp[ptr]}));
            activeDp.erase(activeDp.find(dp[ptr]));
            ptr += 1;
        }

        auto lb = activePsDp.lower_bound({ps[j] + 1, -1});
        if (lb != activePsDp.end())
            dp[j] = lb->second;
        else
            dp[j] = *activeDp.begin() + 1;

        activePsDp.insert({ps[j], dp[j]});
        activeDp.insert(dp[j]);
    }

    cout << dp[N] << endl;
}
