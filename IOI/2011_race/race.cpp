/*
Subproblem:
Given a tree with N nodes, find the minimum number of edges in a path whose total length is exactly K and
it either ends at the root or pass through the root.

      root
    /  |  \
  ..  c_i  c_(i + 1)

After processing the first i children of the root, let's say we know the following:
minEdges[length] -> Minimum number of edges in a path of length "length" such that it originates from the root
and ends up at the subtree of the first i children of the root.

When processing the (i + 1)-th children, we can utilize that value. For example, we are at a node whose distance from
the root is d, then the answer we seek to minize is: depth + minEdges[K - d].

This problem can be solved in O(N) time.

To solve the full problem, we need to perform centroid decomposition. The total complexity will be O(N log(N))
*/

#include "race.h"
#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 200000
#define MAXK 1000000

int n, k, sz[MAXN + 3];
vector<pair<int, int> > adj[MAXN + 3];
bool isDecomposed[MAXN + 3];
int minEdges[MAXK + 3];
int ans = INF;

void dfsSize(int u, int prev = -1) {
  sz[u] = 1;
  for (auto [v, cost]: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      dfsSize(v, u);
      sz[u] += sz[v];
    }
  }
}

int doFindCentroid(int u, int subtreeSize, int prev = -1) {
  for (auto [v, cost]: adj[u]) {
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

void updateAnswer(int u, int prev, int currentDepth, int currentDist) {
  if (k - currentDist >= 1 && k - currentDist <= k) {
    ans = min(ans, currentDepth + minEdges[k - currentDist]);
  }

  for (auto [v, cost]: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      updateAnswer(v, u, currentDepth + 1, currentDist + cost);
    }
  }
}

void updateMinEdges(int u, int prev, int currentDepth, int currentDist) {
  if (currentDist >= 1 && currentDist <= k) {
    minEdges[currentDist] = min(minEdges[currentDist], currentDepth);
  }

  for (auto [v, cost]: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      updateMinEdges(v, u, currentDepth + 1, currentDist + cost);
    }
  }
}

void resetMinEdges(int u, int prev, int currentDist) {
  if (currentDist >= 1 && currentDist <= k) {
    minEdges[currentDist] = INF;
  }

  for (auto [v, cost]: adj[u]) {
    if (v != prev && !isDecomposed[v]) {
      resetMinEdges(v, u, currentDist + cost);
    }
  }
}

void centroidDecomposition(int u) {
  int centroid = findCentroid(u);

  isDecomposed[centroid] = true;

  for (auto [v, cost]: adj[centroid]) {
    if (!isDecomposed[v]) {
      updateAnswer(v, centroid, 1, cost);
      updateMinEdges(v, centroid, 1, cost);
    }
  }

  // Handle paths that end at the centroid
  ans = min(ans, minEdges[k]);

  for (auto [v, cost]: adj[centroid]) {
    if (!isDecomposed[v]) {
      resetMinEdges(v, centroid, cost);
    }
  }

  for (auto [v, cost]: adj[centroid]) {
    if (!isDecomposed[v]) {
      centroidDecomposition(v);
    }
  }
}

int best_path(int N, int K, int H[][2], int L[]) {
  n = N;
  k = K;

  for (int i = 0; i < n - 1; i++) {
    adj[H[i][0]].push_back({H[i][1], L[i]});
    adj[H[i][1]].push_back({H[i][0], L[i]});
  }

  memset(isDecomposed, false, sizeof(isDecomposed));

  minEdges[0] = 0;
  for (int i = 1; i <= k; i++) {
    minEdges[i] = INF;
  }

  centroidDecomposition(0);

  if (ans < INF) {
    return ans;
  } else {
    return -1;
  }
}
