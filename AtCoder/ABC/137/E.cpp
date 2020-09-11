#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 2500
#define MAXM 5000
#define DEBUG true

struct Edge {
    int from, to, weight;
    Edge() {}
    Edge(int _from, int _to, int _weight): from(_from), to(_to), weight(_weight) {}
};

int N, M, P, dist[MAXN + 3];
bool visited[MAXN + 3];
Edge edges[MAXM + 3];
vector<int> adj[MAXN + 3];

bool checkReachability(int u, int target) {
    visited[u] = true;

    if (u == target)
        return true;

    bool result = false;
    for (auto v: adj[u]) {
        if (!visited[v])
            result |= checkReachability(v, target);
    }

    return result;
}

bool isReachable(int u, int v) {
    memset(visited, false, sizeof(visited));
    return checkReachability(u, v);
}

int main() {
    cin >> N >> M >> P;
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        edges[i] = Edge(a, b, -(c - P));
        adj[a].push_back(b);
    }

    //Implement Bellman-Ford algorithm
    for (int i = 1; i <= N; i++)
        dist[i] = INF;

    dist[1] = 0;
    for (int rep = 1; rep < N; rep++) {
        for (int e = 1; e <= M; e++) {
            int u = edges[e].from, v = edges[e].to, w = edges[e].weight;
            if (dist[v] > dist[u] + w)
                dist[v] = dist[u] + w;
        }
    }

    //Check if there is negative cycle in path from 1 to N
    bool negativeCycleExist = false;
    for (int e = 1; e <= M; e++) {
        int u = edges[e].from, v = edges[e].to, w = edges[e].weight;
        if (dist[v] > dist[u] + w && isReachable(1, u) && isReachable(v, N)) {
            negativeCycleExist = true;
        }
    }

    if (negativeCycleExist)
        cout << -1 << endl;
    else
        cout << max(-dist[N], 0) << endl;
}
