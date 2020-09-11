#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000

int n, m, parent[MAXN + 3], sz[MAXN + 3];
vector<int> group[MAXN + 3], groupOf[MAXN + 3];

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

void joinSet(int u, int v) {
    int pu = findSet(u);
    int pv = findSet(v);

    if (pu == pv)
        return;

    parent[pu] = pv;
    sz[pv] += sz[pu];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int g = 1; g <= m; g++) {
        int k, who;

        scanf("%d", &k);
        for (int i = 1; i <= k; i++) {
            scanf("%d", &who);
            group[g].push_back(who);
            groupOf[who].push_back(g);
        }
    }

    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    //connect people in each group
    for (int g = 1; g <= m; g++) {
        for (int i = 1; i < (int) group[g].size(); i++) {
            joinSet(group[g][i], group[g][i - 1]);
        }
    }

    //connect person to other person in every group he belongs to
    for (int who = 1; who <= n; who++) {
        for (auto g: groupOf[who]) {
            //hacky, to prevent connect 'who' to himself
            for (int i = 0; i < min(2, (int) group[g].size()); i++)
                joinSet(who, group[g][i]);
        }
    }

    for (int i = 1; i <= n; i++) {
        printf("%d ", sz[findSet(i)]);
    }
    printf("\n");
}
