#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define INF 10000000

int N, M, S, T, dist[MAXN + 3][3];
vector<int> adj[MAXN + 3];

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
    }
    cin >> S >> T;

    for (int i = 1; i <= MAXN; i++) {
        dist[i][0] = dist[i][1] = dist[i][2] = INF;
    }

    queue<pair<int, int> > Q;

    dist[S][0] = 0;
    Q.push({S, 0});

    while (!Q.empty()) {
        auto front = Q.front(); Q.pop();
        int u = front.first;
        int mod = front.second;

        for (auto v: adj[u]) {
            int nextMod = (mod + 1)%3;
            if (dist[v][nextMod] == INF) {
                dist[v][nextMod] = dist[u][mod] + 1;
                Q.push({v, nextMod});
            }
        }
    }

    if (dist[T][0] < INF && dist[T][0]%3 == 0)
        cout << dist[T][0]/3 << endl;
    else
        cout << -1 << endl;
}
