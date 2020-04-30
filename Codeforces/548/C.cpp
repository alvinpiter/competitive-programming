#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

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

int n, k, cnt;
bool visited[100003];
vector<int> adj[100003];
LL all;

void DFS(int u) {
    cnt += 1;
    visited[u] = true;

    for (auto v: adj[u]) {
        if (!visited[v])
            DFS(v);
    }
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n - 1; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        if (c == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    all = fastExponentiation(n, k);

    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            cnt = 0;
            DFS(i);

            all = (all - fastExponentiation(cnt, k) + MOD)%MOD;
        }
    }

    cout << all << endl;
}
