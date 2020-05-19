#include<bits/stdc++.h>
using namespace std;
#define MAXM 1000
#define MAXN 12
#define INF 1000000000

int N, M, cost[MAXM + 3], dp[MAXM + 3][(1 << MAXN) + 3];
vector<int> adj[MAXM + 3];

/*
Min cost to unlock mask using keys idx..M-1
*/
int solve(int idx, int mask) {
    if (idx == M) {
        if (mask == 0)
            return 0;
        else
            return INF;
    }

    if (dp[idx][mask] != -1)
        return dp[idx][mask];

    int leave = solve(idx + 1, mask);

    int newMask = mask;
    for (auto id: adj[idx]) {
        if (newMask & (1 << id))
            newMask ^= (1 << id);
    }

    int take = cost[idx] + solve(idx + 1, newMask);

    return dp[idx][mask] = min(leave, take);
}

int main() {
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        int b;
        cin >> cost[i] >> b;
        for (int j = 0; j < b; j++) {
            int c;
            cin >> c;

            adj[i].push_back(c - 1);
        }
    }

    memset(dp, -1, sizeof(dp));

    int answer = solve(0, (1 << N) - 1);
    if (answer < INF)
        cout << answer << endl;
    else
        cout << -1 << endl;
}
