/*
Small-to-large merging.

Mantain colors[u], which is a set of colors that appear on the nodes in the subtree rooted at u.

When processing node u, we merge colors[child] to colors[u].
Merging should be done from a smaller-size set to the larger-size set.
By merging this way, each item will change set at most log(N) times. The reason is because in one merging,
it will belong to a set whose size is at least twice as large. Changing set takes log(N) time as well, so
the total complexity of the solution is O(N log^2(N)).
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, color[MAXN + 3], ans[MAXN + 3];
vector<int> adj[MAXN + 3];
set<int> colors[MAXN + 3];

// The result will be stored in u
void merge(int u, int v) {
  if (colors[u].size() < colors[v].size()) {
    swap(colors[u], colors[v]);
  }

  for (auto c: colors[v]) {
    colors[u].insert(c);
  }

  colors[v].clear();
}

void dfs(int u, int prev) {
  for (auto v: adj[u]) {
    if (v != prev) {
      dfs(v, u);
    }
  }

  colors[u].insert(color[u]);
  for (auto v: adj[u]) {
    if (v != prev) {
      merge(u, v);
    }
  }
  ans[u] = colors[u].size();
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> color[i];
  }

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, -1);

  for (int i = 1; i <= n; i++) {
    if (i > 1) cout << " ";
    cout << ans[i];
  }
  cout << endl;
}
