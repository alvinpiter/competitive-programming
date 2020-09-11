#include<bits/stdc++.h>
using namespace std;
#define MAXN 50000
#define MAXK 500
#define LL long long int

//cnt[u][d] -> how many children of node u is at height d.
int N, K, parent[MAXN + 3], cnt[MAXN + 3][MAXK + 3];
vector<int> adj[MAXN + 3];

void DFS(int u, int prv) {
    cnt[u][0] = 1;
    for (auto v: adj[u]) {
        if (v != prv) {
            parent[v] = u;

            DFS(v, u);

            for (int d = 1; d <= K; d++)
                cnt[u][d] += cnt[v][d - 1];
        }
    }
}

int main() {
    cin >> N >> K;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    memset(parent, -1, sizeof(parent));
    memset(cnt, 0, sizeof(cnt));
    DFS(1, 1);

    LL answer = 0;
    for (int u = 1; u <= N; u++) {
        answer += cnt[u][K];

        int current = u;
        int par = parent[u];
        for (int d1 = 1; d1 <= K; d1++) {
            if (par == -1)
                break;

            int d2 = K - d1;

            if (d2 == 0)
                answer += 1;
            else
                answer += (cnt[par][d2] - cnt[current][d2 - 1]);

            current = par;
            par = parent[current];
        }
    }

    cout << answer/2 << endl;
}
