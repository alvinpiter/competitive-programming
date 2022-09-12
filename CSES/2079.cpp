#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, answer, sz[MAXN + 3];
vector<int> adj[MAXN + 3];

void dfs(int u, int prev) {
  sz[u] = 1;
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v != prev) {
      dfs(v, u);
      sz[u] += sz[v];
    }
  }

  bool allBelowThreshold = (n - sz[u] <= n/2);
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v != prev && sz[v] > n/2) {
      allBelowThreshold = false;
    }
  }

  if (allBelowThreshold) {
    answer = u;
  }
}

int main() {
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, -1);

  cout << answer << endl;
}
