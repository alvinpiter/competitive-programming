#include<bits/stdc++.h>
using namespace std;
#define ROOT 1
#define MAXN 100000
#define INF 1e18
#define LL long long int

int N, M;
vector<pair<int, int> > adj[MAXN + 3], adjRev[MAXN + 3];
LL distFromOrigin[MAXN + 3], distFromDestination[MAXN + 3];

vector<int> spAdj[MAXN + 3]; //adjacency list for shortest path graph
int currentDfsTime, dfsTime[MAXN + 3], minDfsTime[MAXN + 3];
set<int> articulationPoints;

void Dijkstra(vector<pair<int, int> > adjList[], LL dist[], int origin) {
    for (int i = 1; i <= N; i++)
        dist[i] = INF;

    priority_queue<pair<LL, int> > PQ;

    dist[origin] = 0;
    PQ.push({-dist[origin], origin});

    while (!PQ.empty()) {
        auto top = PQ.top(); PQ.pop();
        int u = top.second;

        for (auto e: adjList[u]) {
            int v = e.first;
            int cost = e.second;

            if (dist[v] > dist[u] + cost) {
                dist[v] = dist[u] + cost;
                PQ.push({-dist[v], v});
            }
        }
    }
}

void DFS(int u, int prv) {
    dfsTime[u] = ++currentDfsTime;
    minDfsTime[u] = dfsTime[u];

    bool isArticulationPoint = false;
    int spanEdgeFromRootCount = 0;
    for (auto v: spAdj[u]) {
        if (v == prv) continue;

        if (dfsTime[v] == -1) {
            DFS(v, u);
            minDfsTime[u] = min(minDfsTime[u], minDfsTime[v]);

            if (u == ROOT) {
                spanEdgeFromRootCount += 1;
            } else {
                if (minDfsTime[v] >= dfsTime[u])
                    isArticulationPoint = true;
            }
        } else {
            minDfsTime[u] = min(minDfsTime[u], dfsTime[v]);
        }
    }

    if (u == ROOT) {
        if (spanEdgeFromRootCount > 1)
            articulationPoints.insert(ROOT);
    } else {
        if (isArticulationPoint)
            articulationPoints.insert(u);
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v, c;
        cin >> u >> v >> c;

        adj[u].push_back({v, c});
        adjRev[v].push_back({u, c});
    }

    Dijkstra(adj, distFromOrigin, ROOT);
    Dijkstra(adjRev, distFromDestination, N);

    //Construct shortest path graph
    for (int u = 1; u <= N; u++) {
        for (auto e: adj[u]) {
            int v = e.first;
            int cost = e.second;

            LL spLength = distFromOrigin[N];
            if (distFromOrigin[u] + cost + distFromDestination[v] == spLength) {
                spAdj[u].push_back(v);
                spAdj[v].push_back(u);
            }
        }
    }

    currentDfsTime = 0;
    memset(dfsTime, -1, sizeof(dfsTime));
    DFS(ROOT, ROOT);

    //Add origin and destination
    articulationPoints.insert(1);
    articulationPoints.insert(N);

    cout << articulationPoints.size() << endl;
    for (auto u: articulationPoints)
        cout << u << " ";
    cout << endl;
}
