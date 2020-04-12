#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int n, k, parent[MAXN + 3], answer;

int findSet(int u) {
    return (parent[u] == u ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return (findSet(u) == findSet(v));
}

void joinSet(int u, int v) {
    parent[findSet(u)] = findSet(v);
}

int main() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    answer = 0;
    for (int i = 1; i <= k; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        if (isSameSet(u, v)) {
            answer += 1;
        } else {
            joinSet(u, v);
        }
    }

    printf("%d\n", answer);
}
