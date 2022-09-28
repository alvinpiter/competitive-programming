/*
dp[u] = Holds a pair {value, v}, where v is a node under the subtree rooted at u and v is the one with the maximum (av - dist(u, v)).
bestFromParent[u] = Holds a pair {value, v}, where v is a node not in the subtree rooted at u and v is the one with the maximum (av - dist(u, v))
best[u] = aggregation of dp[u] and bestFromParent[u]

Test case:
5 3
1 1 4 5 1
1 2
2 4
2 5
3 5
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1000000001
#define MAXN 300000
#define MAXLG 18

int n, a[MAXN + 3], nxt[MAXN + 3][2];
LL k;
vector<int> adj[MAXN + 3];
pair<int, int> dp[MAXN + 3], bestFromParent[MAXN + 3], best[MAXN + 3];
pair<int, int> MIN_INF = {-INF, 0};

pair<int, int> fillDp(int u, int prev) {
  pair<int, int> best = MIN_INF;
  for (auto v: adj[u]) {
    if (v != prev) {
      auto dpv = fillDp(v, u);
      best = max(best, {dpv.first - 1, dpv.second});
      best = max(best, {a[v] - 1, -v});
    }
  }

  return dp[u] = best;
}

void traverse(int u, int prev) {
  best[u] = max(dp[u], {bestFromParent[u].first - 1, bestFromParent[u].second});

  pair<int, int> bestPrefix = MIN_INF;
  for (auto v: adj[u]) {
    if (v != prev) {
      bestFromParent[v] = max(bestFromParent[v], {bestPrefix.first - 1, bestPrefix.second});
      bestFromParent[v] = max(bestFromParent[v], {a[u], -u});
      bestFromParent[v] = max(bestFromParent[v], {bestFromParent[u].first - 1, bestFromParent[u].second});

      bestPrefix = max(bestPrefix, dp[v]);
      bestPrefix = max(bestPrefix, {a[v], -v});
    }
  }

  pair<int, int> bestSuffix = MIN_INF;
  for (int i = adj[u].size() - 1; i >= 0; i--) {
    int v = adj[u][i];
    if (v != prev) {
      bestFromParent[v] = max(bestFromParent[v], {bestSuffix.first - 1, bestSuffix.second});

      bestSuffix = max(bestSuffix, dp[v]);
      bestSuffix = max(bestSuffix, {a[v], -v});
    }
  }

  for (auto v: adj[u]) {
    if (v != prev) {
      traverse(v, u);
    }
  }
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  fillDp(1, -1);

  for (int i = 1; i <= n; i++) {
    bestFromParent[i] = MIN_INF;
  }
  traverse(1, -1);

  for (int i = 1; i <= n; i++) {
    nxt[i][0] = -best[i].second;
  }

  int current = 1;
  if (k%2 == 1) {
    current = nxt[current][0];
  }

  int t = 0;
  for (int lg = 1; lg <= MAXLG; lg++) {
    t = 1 - t;
    for (int i = 1; i <= n; i++) {
      nxt[i][t] = nxt[nxt[i][1 - t]][1 - t];
    }

    if ((1LL << lg) & k) {
      current = nxt[current][t];
    }
  }

  cout << current << endl;
}
