#include<bits/stdc++.h>
using namespace std;
#define MAXN 300000
#define MAXW 100000

int N, M, dp[MAXN + 3], tempDP[MAXN + 3];
vector<pair<int, int> > weights[MAXW + 3];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        weights[w].push_back({u, v});
    }

    for (int i = 1; i <= N; i++)
        dp[i] = 1;

    for (int w = 1; w <= MAXW; w++) {
        for (int i = 0; i < weights[w].size(); i++)
            tempDP[weights[w][i].second] = dp[weights[w][i].second];

        for (int i = 0; i < weights[w].size(); i++)
            tempDP[weights[w][i].second] = max(tempDP[weights[w][i].second], 1 + dp[weights[w][i].first]);

        for (int i = 0; i < weights[w].size(); i++)
            dp[weights[w][i].second] = tempDP[weights[w][i].second];
    }

    int maxi = 0;
    for (int i = 1; i <= N; i++) maxi = max(maxi, dp[i]);

    cout << maxi - 1 << endl;
}
