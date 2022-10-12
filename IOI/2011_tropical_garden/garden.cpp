/*
Let's build another graph by "splitting" each node of the original original graph. A node u in the original graph will
be split to:
* Node u in the new graph. All edges which are not the best edge in the original graph will be directed to this node.
  Also, this node will have 1 outgoing edge to node v where u-v is the best outgoing edge for u in the original graph.
* Node (u + N) in the new graph. The best edge in the original graph will be directed to this node.
  Also, this node will have 1 outgoing edge to node v where u-v is the second-best outgoing edge for u in the original graph.
  If there's no such v, then just use the best edge.

Notice that our new graph will have 2*N vertices. Now we'd like to count the distance from each node to either
node P or P + N in the new graph. There are 3 cases:
* Node P or (P + N) is not reachable
* Node P or (P + N) is only reachable once
* Node P or (P + N) is reachable multiple times, due to being in a cycle

Instead of starting DFS from each node, we will start DFS from P or (P + N) in the reversed graph, hence DFS is only performed
twice. While doing so, we maintain the distance to each other node and the cycle length if any.

We can then answer the queries by checking each of the 3 cases above and also utilizing the distance and cycle length data.

Total complexity is O(NQ).
*/

#include "garden.h"
#include "gardenlib.h"
#include<bits/stdc++.h>
using namespace std;
#define INF 2000000000
#define MAXN 150000

int N;
vector<pair<int, int> > oriAdj[MAXN + 3]; // {beauty, v}
vector<int> adj[2 * MAXN + 3], revAdj[2 * MAXN + 3];
int dist[2 * MAXN + 3][2], cycleLength[2];
bool visited[2 * MAXN + 3][2];

void addEdgeToNewGraph(int u, int v, int beauty) {
  bool isBestForV = (beauty == oriAdj[v][0].first);
  int resolvedV = (isBestForV ? v + N : v);
  adj[u].push_back(resolvedV);
}

void dfs(int u, int t, int step, int origin) {
  dist[u][t] = step;
  visited[u][t] = true;

  for (auto v: revAdj[u]) {
    if (v == origin) {
      cycleLength[t] = step + 1;
    }

    if (!visited[v][t]) {
      dfs(v, t, step + 1, origin);
    }
  }
}

void count_routes(int n, int m, int p, int r[][2], int q, int g[]) {
  N = n;

  for (int i = 0; i < m; i++) {
    int u = r[i][0], v = r[i][1], beauty = i;
    oriAdj[u].push_back({beauty, v});
    oriAdj[v].push_back({beauty, u});
  }

  for (int u = 0; u < n; u++) {
    sort(oriAdj[u].begin(), oriAdj[u].end());
  }

  for (int u = 0; u < n; u++) {
    // Add directed edge from u to v or (v + n).
    if (true) {
      auto [beauty, v] = oriAdj[u][0];
      addEdgeToNewGraph(u, v, beauty);
    }

    // Add directed edge from (u + n) to v or (v + n).
    if (true) {
      auto [beauty, v] = oriAdj[u].size() > 1 ? oriAdj[u][1] : oriAdj[u][0];
      addEdgeToNewGraph(u + n, v, beauty);
    }
  }

  /*
  Reverse the edges of the new graph.
  This could be done in the previous step, but to make it more understandable, I do it separately.
  */
  for (int u = 0; u < 2 * n; u++) {
    for (auto v: adj[u]) {
      revAdj[v].push_back(u);
    }
  }

  for (int t = 0; t < 2; t++) {
    cycleLength[t] = -1;
    for (int i = 0; i < 2 * n; i++) {
      dist[i][t] = INF;
      visited[i][t] = false;
    }
  }

  dfs(p, 0, 0, p);
  dfs(p + n, 1, 0, p + n);

  for (int query = 0; query < q; query++) {
    int ans = 0;
    for (int u = 0; u < n; u++) {
      bool possible = false;
      for (int t = 0; t < 2; t++) {
        if (dist[u][t] == g[query] || (cycleLength[t] != -1 && g[query] >= dist[u][t] && (g[query] - dist[u][t])%cycleLength[t] == 0)) {
          possible = true;
        }
      }

      if (possible) {
        ans += 1;
      }
    }

    answer(ans);
  }
}
