/*
Counting how many paths of length L that pass through a node u:
Assume after processing the first i children of u, we have cntDepth[h] defined as
the number of decendants of u at depth h. When we are processing descendant of u within
the (i + 1)-th children's subtree, a node at depth k will contribute cntDepth[L - k].

Counting how many paths of length L in the tree:
Apply centroid decomposition. Centroid decomposition disects the tree s.t the size of
each component will be at most N/2. Each of these components can be processed in O(N) time in total.
And since there are at most log(N) disections, the total complexity will be O(N log N).

Possible pitfall:
Remember to reset cntDepth necessarily to avoid TLE.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, k, sz[MAXN + 3], cntDepth[MAXN + 3], maxDepth;
set<int> adj[MAXN + 3];
LL ans;

void dfsSize(int u, int prev = -1) {
  sz[u] = 1;
  for (set<int>::iterator ptr = adj[u].begin(); ptr != adj[u].end(); ++ptr) {
    int v = *ptr;
    if (v != prev) {
      dfsSize(v, u);
      sz[u] += sz[v];
    }
  }
}

int doFindCentroid(int u, int wholeSubtreeSize, int prev = -1) {
  for (set<int>::iterator ptr = adj[u].begin(); ptr != adj[u].end(); ++ptr) {
    int v = *ptr;
    if (v != prev && 2 * sz[v] > wholeSubtreeSize) {
      return doFindCentroid(v, wholeSubtreeSize, u);
    }
  }
  return u;
}

int findCentroid(int u) {
  dfsSize(u);
  return doFindCentroid(u, sz[u]);
}

void countOrFill(int u, bool isFilling, int currentDepth = 1, int prev = -1) {
  if (currentDepth > k) {
    return;
  }

  maxDepth = max(maxDepth, currentDepth);

  if (isFilling) {
    cntDepth[currentDepth] += 1;
  } else {
    ans += cntDepth[k - currentDepth];
  }

  for (set<int>::iterator ptr = adj[u].begin(); ptr != adj[u].end(); ++ptr) {
    int v = *ptr;
    if (v != prev) {
      countOrFill(v, isFilling, currentDepth + 1, u);
    }
  }
}

void decompose(int u) {
  int centroid = findCentroid(u);

  vector<int> children;

  maxDepth = 1;
  for (set<int>::iterator ptr = adj[centroid].begin(); ptr != adj[centroid].end(); ++ptr) {
    int v = *ptr;
    adj[v].erase(centroid);

    children.push_back(v);

    countOrFill(v, false);
    countOrFill(v, true);
  }

  ans += cntDepth[k];

  // Reset cntDepth
  for (int i = 0; i <= maxDepth; i++) {
    cntDepth[i] = 0;
  }

  for (int i = 0; i < children.size(); i++) {
    decompose(children[i]);
  }
}

int main() {
  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);

    adj[u].insert(v);
    adj[v].insert(u);
  }

  ans = 0;

  memset(cntDepth, 0, sizeof(cntDepth));
  decompose(1);

  printf("%lld\n", ans);
}
