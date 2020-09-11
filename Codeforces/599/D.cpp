#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, numCC;
set<int> notAdj[MAXN + 3];
set<int> unvisitedVertices;

void DFS(int u) {
    unvisitedVertices.erase(u);

    int v = 0;
    while (unvisitedVertices.upper_bound(v) != unvisitedVertices.end()) {
        v = *unvisitedVertices.upper_bound(v);
        if (unvisitedVertices.find(v) == unvisitedVertices.end()) continue; //v is already visited
        if (notAdj[u].find(v) != notAdj[u].end()) continue; //v is not neighbor of u
        DFS(v);
    }
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        notAdj[u].insert(v);
        notAdj[v].insert(u);
    }

    for (int i = 1; i <= N; i++)
        unvisitedVertices.insert(i);

    numCC = 0;
    for (int i = 1; i <= N; i++) {
        if (unvisitedVertices.find(i) != unvisitedVertices.end()) {
            numCC += 1;
            DFS(i);
        }
    }

    printf("%d\n", numCC - 1);
}
