#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXLG 18

int n, q, P[MAXN + 3][MAXLG + 3];
vector<int> children[MAXN + 3];

void DFS(int u) {
    for (auto v: children[u]) {
        P[v][0] = u;
        DFS(v);
    }
}

int getKthParent(int x, int k) {
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (k & (1 << lg)) {
            if (x == -1)
                break;
            else
                x = P[x][lg];
        }
    }

    return x;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);

        children[p].push_back(i);
    }

    memset(P, -1, sizeof(P));
    DFS(1);

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= n; i++) {
            if (P[i][lg - 1] != -1)
                P[i][lg] = P[P[i][lg - 1]][lg - 1];
        }
    }

    for (int i = 1; i <= q; i++) {
        int x, k;
        scanf("%d%d", &x, &k);

        printf("%d\n", getKthParent(x, k));
    }
}
