#include<bits/stdc++.h>
using namespace std;
#define MAXN 400000
#define MAXLG 20

int N, P[MAXN + 3][MAXLG + 1], depth[MAXN + 3], answer[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS(int u, int prev) {
    P[u][0] = prev;
    depth[u] = depth[prev] + 1;

    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != prev)
            DFS(v, u);
    }
}

void initParent() {
    for (int j = 1; j <= MAXLG; j++) {
        for (int i = 1; i <= N; i++) {
            P[i][j] = P[P[i][j - 1]][j - 1];
        }
    }
}

int getKthParent(int u, int k) {
    int parent = u;
    for (int i = 0; i <= MAXLG; i++) {
        if (k & (1 << i))
            parent = P[parent][i];
    }

    return parent;
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    if (diff != 0)
        v = getKthParent(v, diff);

    if (u == v)
        return u;

    for (int i = MAXLG; i >= 0; i--) {
        if (P[u][i] != 0 && P[u][i] != P[v][i]) {
            u = P[u][i];
            v = P[v][i];
        }
    }

    return P[u][0];
}

void aggregateAnswer(int u, int prev) {
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];

        if (v != prev) {
            aggregateAnswer(v, u);
            answer[u] += answer[v];
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(P, 0, sizeof(P));
    memset(answer, 0, sizeof(answer));

    depth[0] = 0;
    DFS(1, 0);

    initParent();

    for (int i = 2; i <= N; i++) {
        int lca = getLCA(i - 1, i);

        if (lca == i - 1) {
            answer[i] += 1;
            answer[P[lca][0]] -= 1;
        } else if (lca == i) {
            answer[i - 1] += 1;
            answer[P[lca][0]] -= 1;
        } else {
            answer[i - 1] += 1;
            answer[i] += 1;
            answer[lca] -= 1;
            answer[P[lca][0]] -= 1;
        }
    }

    aggregateAnswer(1, 0);

    for (int i = 1; i <= N; i++)
        printf("%d\n", answer[i]);
}
