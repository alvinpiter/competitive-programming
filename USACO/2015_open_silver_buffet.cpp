#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int N, E, quality[MAXN + 3], dist[MAXN + 3][MAXN + 3], dp[MAXN + 3];
bool cached[MAXN + 3];
vector<int> adj[MAXN + 3];

void BFS(int u) {
    dist[u][u] = 0;

    queue<int> q;
    q.push(u);

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (auto neighbor: adj[curr]) {
            if (dist[u][neighbor] == -1) {
                dist[u][neighbor] = dist[u][curr] + 1;
                q.push(neighbor);
            }
        }
    }
}

//maximal quality reachable if we start from node u
int solve(int u) {
    if (cached[u])
        return dp[u];

    int result = quality[u];
    for (int v = 1; v <= N; v++) {
        if (u != v && dist[u][v] != -1 && quality[v] > quality[u]) {
            result = max(result, solve(v) + (quality[u] - dist[u][v] * E));
        }
    }

    cached[u] = true;
    return dp[u] = result;
}

int main() {
    freopen("buffet.in", "r", stdin);
    freopen("buffet.out", "w", stdout);

    cin >> N >> E;
    for (int i = 1; i <= N; i++) {
        cin >> quality[i];

        int cnt;
        cin >> cnt;
        for (int j = 1; j <= cnt; j++) {
            int v;
            cin >> v;

            adj[i].push_back(v);
            adj[v].push_back(i);
        }
    }

    memset(dist, -1, sizeof(dist));
    for (int i = 1; i <= N; i++) {
        BFS(i);
    }

    memset(cached, false, sizeof(cached));

    int answer = 0;
    for (int i = 1; i <= N; i++)
        answer = max(answer, solve(i));

    cout << answer << endl;
}
