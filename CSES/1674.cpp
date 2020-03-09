#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, sz[MAXN + 3];
vector<int> children[MAXN + 3];

void DFS(int u) {
    sz[u] = 1;
    for (auto v: children[u]) {
        DFS(v);
        sz[u] += sz[v];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);

        children[p].push_back(i);
    }

    DFS(1);
    for (int i = 1; i <= n; i++) {
        if (i > 1)
            printf(" ");

        printf("%d", sz[i] - 1);
    }
    printf("\n");
}
