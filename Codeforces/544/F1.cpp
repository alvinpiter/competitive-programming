#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, m, inDegree[MAXN + 3];
bool visited[MAXN + 3];
vector<int> adj[MAXN + 3];
vector<pair<int, int> > answer;

int main() {
    cin >> n >> m;

    memset(inDegree, 0, sizeof(inDegree));
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        inDegree[u] += 1;
        inDegree[v] += 1;
    }

    int best = 1;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] > inDegree[best])
            best = i;
    }

    queue<int> Q;
    Q.push(best);

    memset(visited, false, sizeof(visited));
    visited[best] = true;

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (auto v: adj[u]) {
            if (visited[v] == false) {
                answer.push_back({u, v});

                visited[v] = true;
                Q.push(v);
            }
        }
    }

    for (auto a: answer) {
        cout << a.first << " " << a.second << endl;
    }
}
