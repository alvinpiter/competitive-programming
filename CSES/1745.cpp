#include<bits/stdc++.h>
using namespace std;
#define MAXN 100
#define MAXV 100000

int N, X[MAXN + 3];
bool dp[MAXV + 3];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> X[i];

    memset(dp, false, sizeof(dp));

    dp[0] = true;
    for (int i = 1; i <= N; i++) {
        for (int sum = MAXV; sum >= 1; sum--) {
            if (sum >= X[i] && dp[sum - X[i]] == true)
                dp[sum] = true;
        }
    }

    vector<int> possibleSums;
    for (int i = 1; i <= MAXV; i++) {
        if (dp[i] == true)
            possibleSums.push_back(i);
    }

    cout << possibleSums.size() << endl;
    for (int i = 0; i < possibleSums.size(); i++) {
        if (i > 0)
            cout << " ";

        cout << possibleSums[i];
    }
    cout << endl;
}
