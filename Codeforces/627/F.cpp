#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, A[MAXN + 3], costDown[MAXN + 3], answer[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS1(int u, int prv) {
    costDown[u] = A[u];
    for (auto v: adj[u]) {
        if (v != prv) {
            DFS1(v, u);
            costDown[u] += max(costDown[v], 0);
        }
    }
}

void DFS2(int u, int prv) {
    answer[u] = costDown[u];

    for (auto v: adj[u]) {
        if (v != prv) {
            int tempCostDownU = costDown[u];
            int tempCostDownV = costDown[v];

            costDown[u] -= max(costDown[v], 0);
            costDown[v] += max(costDown[u], 0);

            DFS2(v, u);

            costDown[u] = tempCostDownU;
            costDown[v] = tempCostDownV;
        }
    }
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        A[i] = (A[i] == 0 ? -1 : 1);
    }

    for (int i = 1; i <= N - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS1(1, 1);
    DFS2(1, 1);

    for (int i = 1; i <= N; i++)
        cout << answer[i] << " ";
    cout << endl;
}
