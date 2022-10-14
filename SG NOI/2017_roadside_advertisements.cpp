/*
Define "crucial" nodes as a set of nodes involving a, b, c, d, and e, such that
the LCA of every subset these nodes exists in the set.

To answer the query, we only need to process these crucial nodes starting from the deepest one.
From a crucial node, we go up to the next crucial node and add the distance to the answer.
Do this for every crucial node.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXV 50000
#define MAXLG 15

int V, Q, level[MAXV + 3], tin[MAXV + 3], tout[MAXV + 3], depth[MAXV + 3], dfsTime;
int P[MAXV + 3][MAXLG + 3];
set<int> crucialNodes;
bool isProcessed[MAXV + 3];
vector<pair<int, int> > adj[MAXV + 3];

void dfs(int u, int prev = -1) {
  tin[u] = ++dfsTime;
  for (auto [v, w]: adj[u]) {
    if (v != prev) {
      level[v] = level[u] + 1;
      depth[v] = depth[u] + w;
      P[v][0] = u;
      dfs(v, u);
    }
  }

  tout[u] = dfsTime;
}

int getLCA(int u, int v) {
  if (level[u] > level[v]) {
    swap(u, v);
  }

  int levelDiff = level[v] - level[u];
  for (int lg = 0; lg <= MAXLG; lg++) {
    if (levelDiff & (1 << lg)) {
      v = P[v][lg];
    }
  }

  if (u == v) {
    return u;
  }

  for (int lg = MAXLG; lg >= 0; lg--) {
    if (P[u][lg] != P[v][lg]) {
      u = P[u][lg];
      v = P[v][lg];
    }
  }

  return P[u][0];
}

int goUp(int u) {
  isProcessed[u] = true;

  // Find the next crucial node to visit
  int nextNode = -1;
  for (auto v: crucialNodes) {
    if (v != u && tin[v] <= tin[u] && tout[v] >= tout[u]) {
      if (nextNode == -1 || level[v] > level[nextNode]) {
        nextNode = v;
      }
    }
  }

  if (nextNode == -1) {
    return 0;
  } else {
    return (depth[u] - depth[nextNode]) + (!isProcessed[nextNode] ? goUp(nextNode) : 0);
  }
}

int main() {
  cin >> V;
  for (int i = 0; i < V - 1; i++) {
    int u, v, w;
    cin >> u >> v >> w;

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  level[1] = depth[1] = 0;
  P[1][0] = -1;
  dfsTime = 0;

  dfs(0);

  for (int lg = 1; lg <= MAXLG; lg++) {
    for (int i = 0; i < V; i++) {
      if (P[i][lg - 1] != -1) {
        P[i][lg] = P[P[i][lg - 1]][lg - 1];
      } else {
        P[i][lg] = -1;
      }
    }
  }

  cin >> Q;

  memset(isProcessed, false, sizeof(isProcessed));
  for (int query = 0; query < Q; query++) {
    int nodes[5];
    for (int i = 0; i < 5; i++) {
      cin >> nodes[i];
    }

    for (int mask = 1; mask < 32; mask++) {
      int currentLCA = -1;
      for (int i = 0; i < 5; i++) {
        if (mask & (1 << i)) {
          currentLCA = (currentLCA == -1 ? nodes[i] : getLCA(currentLCA, nodes[i]));
        }
      }

      crucialNodes.insert(currentLCA);
    }

    int ans = 0;
    for (auto node: crucialNodes) {
      if (!isProcessed[node]) {
        ans += goUp(node);
      }
    }

    cout << ans << endl;

    // Reset crucialNodes and isProcessed
    for (auto node: crucialNodes) {
      isProcessed[node] = false;
    }
    crucialNodes.clear();
  }
}
