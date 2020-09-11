#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000
#define LL long long int

int N, answer, P[MAXN + 3];
LL sum[MAXN + 3], all, mini;
vector<int> adj[MAXN + 3];

void DFS(int u, int prev) {
    sum[u] = P[u];

    LL maxChildrenCost = 0;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != prev) {
            DFS(v, u);
            sum[u] += sum[v];

            maxChildrenCost = max(maxChildrenCost, sum[v]);
        }
    }

    LL maxCost = max(maxChildrenCost, (all - sum[u]));
    if (maxCost < mini) {
        mini = maxCost;
        answer = u;
    }
}

int main() {
    cin >> N;

    all = 0;
    for (int i = 0; i < N; i++) {
        cin >> P[i];
        all += P[i];
    }

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    mini = 1e18;
    DFS(0, 0);

    cout << answer << endl;
}
