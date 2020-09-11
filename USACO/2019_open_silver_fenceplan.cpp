#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define SZ pair<pair<int, int>, pair<int, int> >

int N, M, x[MAXN + 3], y[MAXN + 3], visited[MAXN + 3], answer;
vector<int> adj[MAXN + 3];

//return {{minX, maxX}, {minY, maxY}}
SZ DFS(int u) {
    visited[u] = true;

    SZ result = {{x[u], x[u]}, {y[u], y[u]}};
    for (auto v: adj[u]) {
        if (!visited[v]) {
            auto res = DFS(v);
            result.first.first = min(result.first.first, res.first.first);
            result.first.second = max(result.first.second, res.first.second);
            result.second.first = min(result.second.first, res.second.first);
            result.second.second = max(result.second.second, res.second.second);
        }
    }

    return result;
}

int main() {
    freopen("fenceplan.in", "r", stdin);
    freopen("fenceplan.out", "w", stdout);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    answer = 1e9;

    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            auto result = DFS(i);
            answer = min(answer, 2 * (result.first.second - result.first.first + result.second.second - result.second.first));
        }
    }

    cout << answer << endl;
}
