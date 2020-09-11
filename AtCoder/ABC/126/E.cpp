#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, numCC;
vector<int> adj[MAXN + 3];
bool visited[MAXN + 3];

void DFS(int u) {
    visited[u] = true;
    for (auto v: adj[u]) {
        if (visited[v] == false)
            DFS(v);
    }
}

int main() {
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        int X, Y, Z;
        cin >> X >> Y >> Z;

        adj[X].push_back(Y);
        adj[Y].push_back(X);
    }

    memset(visited, false, sizeof(visited));

    numCC = 0;
    for (int i = 1; i <= N; i++) {
        if (visited[i] == false) {
            numCC += 1;
            DFS(i);
        }
    }

    cout << numCC << endl;
}
