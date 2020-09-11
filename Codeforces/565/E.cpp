#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int t, n, m, color[MAXN + 3];
vector<int> adj[MAXN + 3];

void DFS(int u) {
    for (auto v: adj[u]) {
        if (color[v] == -1) {
            color[v] = 1 - color[u];
            DFS(v);
        }
    }
}

int main() {
    scanf("%d", &t);
    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            color[i] = -1;
        }

        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        color[1] = 0;
        DFS(1);

        int numWhite = 0, numBlack = 0;
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) numWhite += 1;
            if (color[i] == 1) numBlack += 1;
        }

        if (numWhite < numBlack) {
            printf("%d\n", numWhite);
            for (int i = 1; i <= n; i++) {
                if (color[i] == 0)
                    printf("%d ", i);
            }
        } else {
            printf("%d\n", numBlack);
            for (int i = 1; i <= n; i++) {
                if (color[i] == 1)
                    printf("%d ", i);
            }
        }
        printf("\n");
    }
}
