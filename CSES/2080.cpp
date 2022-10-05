/*
Let's solve a subproblem:
Given a tree with N nodes. How many paths of length K that either ends at the root or pass through the root?

      root
    /  |   \
  c1   c2   c3

We can solve the problem by maintaining the number of nodes at a certain depth.
For example, if we know how many nodes at a certain depth in the subtree c1, we can calculate how many paths with length
K that ends at node u, where u is a node in the subtree c2. The formula: cntAtDepth[K - 2 - depth[u]]. In the end, we need
to add cntAtDepth[K - 1], this is for paths that ends at the root.

Doing the above for each node might result in TLE. Centroid decomposition to the rescue.
* We first solve the problem if we assume the root is the centroid of the tree. This takes O(N) in total.
* Then we recursively solve the problem for each subtree neighboring to the centroid. This also takes O(N) in total.
* Since we can only decompose a tree at most log(N) times, the total complexity of the solution is O(N log(N)).
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n, k, sz[MAXN + 3], cntAtDepth[MAXN + 3];
vector<int> adj[MAXN + 3];
bool isDecomposed[MAXN + 3];
LL ans = 0;

void dfsSize(int u, int prev = -1) {
  sz[u] = 1;
  for (auto v: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      dfsSize(v, u);
      sz[u] += sz[v];
    }
  }
}

int doFindCentroid(int u, int subtreeSize, int prev = -1) {
  for (auto v: adj[u]) {
    if (v != prev && !isDecomposed[v] && sz[v] * 2 > subtreeSize) {
      return doFindCentroid(v, subtreeSize, u);
    }
  }

  return u;
}

int findCentroid(int u) {
  dfsSize(u);
  return doFindCentroid(u, sz[u]);
}

void accumulateCnt(int u, int prev = -1, int depth = 0) {
  ans += (k - 2 - depth >= 0 ? cntAtDepth[k - 2 - depth] : 0); // sibling -> centroid -> current
  for (auto v: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      accumulateCnt(v, u, depth + 1);
    }
  }
}

void updateCnt(int u, int updateBy, int prev = -1, int depth = 0) {
  cntAtDepth[depth] += updateBy;
  for (auto v: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      updateCnt(v, updateBy, u, depth + 1);
    }
  }
}

void centroidDecomposition(int u) {
  int centroid = findCentroid(u);

  isDecomposed[centroid] = true;

  // Count the number of paths that pass through the centroid
  for (auto v: adj[centroid]) {
    if (!isDecomposed[v]) {
      accumulateCnt(v);
      updateCnt(v, 1);
    }
  }

  // Special case, path that ends at the centroid
  ans += cntAtDepth[k - 1];

  // Reset cntAtDepth
  for (auto v: adj[centroid]) {
    if (!isDecomposed[v]) {
      updateCnt(v, -1);
    }
  }

  for (auto v: adj[centroid]) {
    if (!isDecomposed[v]) {
      centroidDecomposition(v);
    }
  }
}

int main() {
  cin >> n >> k;
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  memset(isDecomposed, false, sizeof(isDecomposed));
  memset(cntAtDepth, 0, sizeof(cntAtDepth));
  centroidDecomposition(1);

  cout << ans << endl;
}
