#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e16
#define MAXN 300000

/*
Algorithm:
* Construct shortest path DAG
* Remove all edges that is not part of shortest path DAG
* For all the remaining edgesin SP DAG, calculate in degree of each nodes.
* Remove all edges that destined to a node with indegree > 1
* Remove all end nodes (node with outdegree 0).

Alternative algorithm:
Dijsktra's algorithm, but stop when we have used k edges.
*/

struct Edge {
    int to, weight, index;
    Edge(int _to, int _weight, int _index): to(_to), weight(_weight), index(_index) {}
};

int n, m, k, numOfEdgesToBeDeleted;
LL dist[MAXN + 3];
bool deleted[MAXN + 3]; //whether edge i is deleted
vector<Edge> adj[MAXN + 3];

void deleteEndNode(int u) {
    for (auto e: adj[u]) {
        if (dist[e.to] == dist[u] + e.weight && !deleted[e.index])
            deleteEndNode(e.to);
    }

    for (auto e: adj[u]) {
        if (dist[e.to] == dist[u] + e.weight && !deleted[e.index] && numOfEdgesToBeDeleted > 0) {
            deleted[e.index] = true;
            numOfEdgesToBeDeleted -= 1;
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back(Edge(v, w, i));
        adj[v].push_back(Edge(u, w, i));
    }

    //Dijkstra's
    for (int i = 1; i <= n; i++)
        dist[i] = INF;

    priority_queue<pair<LL, int> > pq;

    dist[1] = 0;
    pq.push({-dist[1], 1});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        int u = top.second;
        LL d = -top.first;

        if (d > dist[u])
            continue;

        for (auto e: adj[u]) {
            if (dist[e.to] > dist[u] + e.weight) {
                dist[e.to] = dist[u] + e.weight;
                pq.push({-dist[e.to], e.to});
            }
        }
    }

    memset(deleted, false, sizeof(deleted));
    numOfEdgesToBeDeleted = m - k;

    //If an edge does not belong to shortest path DAG, delete it
    for (int u = 1; u <= n; u++) {
        for (auto e: adj[u]) {
            int v = e.to;
            if (dist[u] != dist[v] + e.weight && dist[v] != dist[u] + e.weight && !deleted[e.index]) {
                deleted[e.index] = true;
                numOfEdgesToBeDeleted -= 1;
            }
        }
    }

    int inDegree[MAXN + 3]; //inDegree of nodes in shortest path DAG
    memset(inDegree, 0, sizeof(inDegree));
    for (int u = 1; u <= n; u++) {
        for (auto e: adj[u]) {
            int v = e.to;
            if (dist[v] == dist[u] + e.weight)
                inDegree[v] += 1;
        }
    }

    //If a node has more than one in degree, delete all but one.
    for (int u = 1; u <= n; u++) {
        for (auto e: adj[u]) {
            int v = e.to;
            if (dist[v] == dist[u] + e.weight && inDegree[v] > 1) {
                inDegree[v] -= 1;
                deleted[e.index] = true;
                numOfEdgesToBeDeleted -= 1;
            }
        }
    }

    deleteEndNode(1);

    set<int> answer;
    for (int u = 1; u <= n; u++) {
        for (auto e: adj[u]) {
            if (!deleted[e.index])
                answer.insert(e.index);
        }
    }

    printf("%d\n", (int) answer.size());
    for (auto a: answer)
        printf("%d ", a);
    printf("\n");
}
