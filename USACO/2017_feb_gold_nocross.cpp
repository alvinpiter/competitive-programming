#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

/*
dp[i][j] -> how many road can be built from the suffix i..N and j..N
*/

int N, first[MAXN + 3], second[MAXN + 3], dp[MAXN + 3][MAXN + 3];
vector<int> nxt[MAXN + 3]; //nxt[i] -> indices of element on the second row such that |first[i] - second[j]| <= 4

int solve(int i, int j) {
    if (i == N + 1 || j == N + 1)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int skip = solve(i + 1, j);
    int take = 0;

    //If we decide to pair i with something, it's better to pair it with the smallest index
    int idx = lower_bound(nxt[i].begin(), nxt[i].end(), j) - nxt[i].begin();
    if (idx < nxt[i].size())
        take = 1 + solve(i + 1, nxt[i][idx] + 1);

    return dp[i][j] = max(skip, take);
}

int main() {
    freopen("nocross.in", "r", stdin);
    freopen("nocross.out","w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> first[i];

    for (int i = 1; i <= N; i++)
        cin >> second[i];

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (abs(first[i] - second[j]) <= 4)
                nxt[i].push_back(j);
        }
    }

    memset(dp, -1, sizeof(dp));

    cout << solve(1, 1) << endl;
}
