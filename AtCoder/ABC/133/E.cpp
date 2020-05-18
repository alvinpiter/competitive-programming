#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 100000

LL fastExponentiation(LL base, int p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

int N, K;
vector<int> adj[MAXN + 3];
LL fact[MAXN + 3], answer;

LL P(int n, int k) {
    if (n < k)
        return 0;

    LL numerator = fact[n];
    LL denominator = fastExponentiation(fact[n - k], MOD - 2);
    return (numerator * denominator)%MOD;
}

void dfs(int u, int prv, int depth) {
    if (depth == 0) {
        int numChild = (int) adj[u].size();
        answer = (answer * P(K, numChild + 1))%MOD; //number of ways to color the first 2 depth
    } else {
        int numChild = (int) adj[u].size() - 1;
        answer = (answer * P(K - 2, numChild))%MOD;
    }

    for (auto v: adj[u]) {
        if (v != prv)
            dfs(v, u, depth + 1);
    }
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    cin >> N >> K;
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    answer = 1;
    dfs(1, 1, 0);

    cout << answer << endl;
}
