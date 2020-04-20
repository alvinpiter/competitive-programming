#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000
#define MOD 1000000007

LL fact[MAXN + 3], dp[MAXN + 3], answer[MAXN + 3];
int N, sz[MAXN + 3];
vector<int> adj[MAXN + 3];

LL fastExponentiation(int base, int p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

void DFS(int u, int prv) {
    sz[u] = 1;
    for (auto v: adj[u]) {
        if (v != prv) {
            DFS(v, u);
            sz[u] += sz[v];
        }
    }
}

void fillDp(int u, int prv) {
    dp[u] = fact[sz[u] - 1];
    for (auto v: adj[u]) {
        if (v != prv) {
            fillDp(v, u);

            dp[u] = (dp[u] * dp[v])%MOD;
            dp[u] = (dp[u] * fastExponentiation(fact[sz[v]], MOD - 2))%MOD;
        }
    }
}

void reroot(int u, int prv) {
    answer[u] = dp[u];
    for (int v: adj[u]) {
        if (v != prv) {
            LL tempDpU = dp[u];
            int tempSzU = sz[u];
            LL tempDpV = dp[v];
            int tempSzV = sz[v];

            //Adjust u
            sz[u] -= tempSzV;
            dp[u] = (dp[u] * fastExponentiation(fact[tempSzU - 1], MOD - 2))%MOD;
            dp[u] = (dp[u] * fact[sz[u] - 1])%MOD;
            dp[u] = (dp[u] * fastExponentiation(tempDpV, MOD - 2))%MOD;
            dp[u] = (dp[u] * fact[tempSzV])%MOD;

            //Adjust v
            sz[v] += sz[u];
            dp[v] = (dp[v] * fastExponentiation(fact[tempSzV - 1], MOD - 2))%MOD;
            dp[v] = (dp[v] * fact[sz[v] - 1])%MOD;
            dp[v] = (dp[v] * dp[u])%MOD;
            dp[v] = (dp[v] * fastExponentiation(fact[sz[u]], MOD - 2))%MOD;

            reroot(v, u);

            dp[u] = tempDpU;
            sz[u] = tempSzU;
            dp[v] = tempDpV;
            sz[v] = tempSzV;
        }
    }
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    cin >> N;
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(1, 1);
    fillDp(1, 1);

    reroot(1, 1);

    for (int i = 1; i <= N; i++)
        cout << answer[i] << endl;
}
