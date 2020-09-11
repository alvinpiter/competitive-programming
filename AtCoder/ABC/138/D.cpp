#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, Q, ans[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS(int u, int prv) {
    for (auto v: adj[u]) {
        if (v != prv) {
            ans[v] += ans[u];
            DFS(v, u);
        }
    }
}

int main() {
    cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= Q; i++) {
        int p, x;
        cin >> p >> x;

        ans[p] += x;
    }

    DFS(1, 1);

    for (int i = 1; i <= N; i++)
        cout << ans[i] << " ";
    cout << endl;
}
