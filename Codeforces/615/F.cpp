#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, dist[MAXN + 3], prv[MAXN + 3], A, B, C, diameter, totalLength;
vector<int> adj[MAXN + 3];

void DFS(int u, int p) {
    for (auto v: adj[u]) {
        if (v != p) {
            dist[v] = dist[u] + 1;
            prv[v] = u;
            DFS(v, u);
        }
    }
}

int getFarthestNode() {
    int ans = 1;
    for (int i = 1; i <= N; i++) {
        if (dist[i] > dist[ans])
            ans = i;
    }

    return ans;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i < N; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dist[1] = 0;
    prv[1] = -1;
    DFS(1, 1);

    A = getFarthestNode();
    dist[A] = 0;
    prv[A] = -1;
    DFS(A, A);

    B = getFarthestNode();

    diameter = dist[B];

    memset(dist, -1, sizeof(dist));
    queue<int> Q;

    //Push all nodes that belong to diameter to queue
    int current = B;
    while (current != -1) {
        dist[current] = 0;
        Q.push(current);

        current = prv[current];
    }

    //Multi source BFS
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (auto v: adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                prv[v] = u;
                Q.push(v);
            }
        }
    }

    C = getFarthestNode();

    //Edge case, line graph
    if (dist[C] == 0) {
        for (int i = 1; i <= N; i++) {
            if (i != A && i != B)
                C = i;
        }
    }

    totalLength = diameter + dist[C];

    cout << totalLength << endl;
    cout << A << " " << B << " " << C << endl;
}
