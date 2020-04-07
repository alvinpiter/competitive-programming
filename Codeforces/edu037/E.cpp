#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, m, numCC, sz[MAXN + 3];
set<int> notAdj[MAXN + 3];
set<int> notVisitedVertices;

void DFS(int u) {
    notVisitedVertices.erase(u);

    sz[numCC] += 1;

    int v = 0;
    while (notVisitedVertices.upper_bound(v) != notVisitedVertices.end()) {
        v = *notVisitedVertices.upper_bound(v);
        if (notVisitedVertices.find(v) == notVisitedVertices.end()) continue; //v is already visited
        if (notAdj[u].find(v) != notAdj[u].end()) continue; //v is not neighbor of u
        DFS(v);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        notAdj[u].insert(v);
        notAdj[v].insert(u);
    }

    for (int i = 1; i <= n; i++) {
        notVisitedVertices.insert(i);
    }

    numCC = 0;
    memset(sz, 0, sizeof(sz));
    for (int u = 1; u <= n; u++) {
        if (notVisitedVertices.find(u) != notVisitedVertices.end()) {
            numCC += 1;
            DFS(u);
        }
    }

    printf("%d\n", numCC);

    sort(sz + 1, sz + numCC + 1);
    for (int i = 1; i <= numCC; i++)
        printf("%d ", sz[i]);
    printf("\n");
}
