#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define INF 1e9

int N, a[MAXN + 3], smallest[MAXN + 3], answer[MAXN + 3], currentLIS;
vector<int> adj[MAXN + 3];

void DFS(int u, int prv) {
    int pos = lower_bound(smallest, smallest + currentLIS, a[u]) - smallest;

    int prvValue = smallest[pos];
    bool increaseLIS = (pos == currentLIS);

    if (pos == currentLIS)
        currentLIS += 1;

    smallest[pos] = a[u];
    answer[u] = currentLIS;

    for (auto v: adj[u]) {
        if (v != prv)
            DFS(v, u);
    }

    //Undo everything
    if (increaseLIS)
        currentLIS -= 1;

    smallest[pos] = prvValue;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    currentLIS = 0;
    for (int i = 0; i <= N; i++)
        smallest[i] = INF;

    DFS(1, 1);

    for (int i = 1; i <= N; i++)
        printf("%d\n", answer[i]);
}
