#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define MOD 1000000007

/*
dp[u][c] -> number of ways of coloring subtree u where node u is colored c.
*/

int N, K, color[MAXN + 3];
vector<int> adj[MAXN + 3];
LL dp[MAXN + 3][4];

LL solve(int prv, int u, int c) {
    if (dp[u][c] != -1)
        return dp[u][c];

    if (color[u] != -1 && color[u] != c)
        return 0;

    LL result = 1;
    for (auto v: adj[u]) {
        if (v != prv) {
            LL temp = 0;
            for (int nxtc = 1; nxtc <= 3; nxtc++) {
                if (nxtc != c) {
                    temp = (temp + solve(u, v, nxtc))%MOD;
                }
            }

            result = (result * temp)%MOD;
        }
    }

    return dp[u][c] = result;
}

int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);

    cin >> N >> K;
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(color, -1, sizeof(color));
    for (int i = 1; i <= K; i++) {
        int b, c;
        cin >> b >> c;
        color[b] = c;
    }

    memset(dp, -1, sizeof(dp));

    cout << (solve(0, 1, 1) + solve(0, 1, 2) + solve(0, 1, 3))%MOD << endl;
}
