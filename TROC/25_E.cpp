/*
There are 2 ways of solving this problem.

First way is BFS ordering trick:
* Order the nodes according to the visitation order of a BFS algorithm.
* Direct children of node u will be ordered consecutively, hence we can perform
  the update/query using a segment tree (range update/query). Don't forget
  to take into account node u's parent.

Second way is with SQRT decomposition batch update.
Reference: https://usaco.guide/plat/sqrt?lang=cpp#batching

The idea is as follows:
1. A[i] -> the value of node i. ans[i] -> the answer to the "query i".
2. Calculating ans[i] will take O(N) time.
3. We maintain a vector named pendingUpdates, which will store the updates
  that we HAVEN'T applied. The format of the data is {nodeIndex, val}, meaning
  we will spread val to nodeIndex's neighbors.
4. Whenever a new update is executed, i.e "update x", we need to first find out node x's current
  value. We can do this by iterating the pendingUpdates vector and take into account all updates
  happening on the neighbors of x.
5. Whenever a query is executed, i.e "query x", we again need to iterate pendingUpdates vector and
  take into account all updates happening on node x and nodes within distance 2 from x.
  To check whether a node y is at distance 2 from x, we can do the following:
  * Is parent[parent[x]] = y?
  * Is parent[parent[y]] = x?
  * Is parent[x] = parent[y]?
6. The final thing to note is that, pendingUpdates' size should never be larger than SQRT(N).
   This ensures:
   * The total time taken by step 4 is Q*SQRT(N).
   * The total time taken by step 5 is Q*SQRT(N).

   When the pendingUpdates' size is SQRT(N), we will apply the updates by doing step 2 and then clear the vector.
   Step 2 will be called at most (Q/SQRT(N)) times. Hence the total time taken is Q*SQRT(N).
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 998244353
#define THRESHOLD 320
#define MAXN 100000

int N, Q, A[MAXN + 3], parent[MAXN + 3];
LL ans[MAXN + 3], updateMap[MAXN + 3];
vector<int> adj[MAXN + 3];
vector<pair<int, int> > pendingUpdates; // {nodeIndex, value}

void dfs(int u, int prev = -1) {
  for (auto v: adj[u]) {
    if (v != prev) {
      parent[v] = u;
      dfs(v, u);
    }
  }
}

void applyPendingUpdates() {
  memset(updateMap, 0, sizeof(updateMap));
  for (auto [y, val]: pendingUpdates) {
    updateMap[y] = (updateMap[y] + val)%MOD;
  }

  // Calculate A(s)
  for (int u = 1; u <= N; u++) {
    for (auto v: adj[u]) {
      A[u] = (A[u] + updateMap[v])%MOD;
    }
  }

  // Calculate ans(s)
  for (int u = 1; u <= N; u++) {
    ans[u] = 0;
    for (auto v: adj[u]) {
      ans[u] = (ans[u] + A[v])%MOD;
    }
  }

  pendingUpdates.clear();
}

void update(int x) {
  int currentVal = A[x];
  for (auto [y, val]: pendingUpdates) {
    if (parent[x] == y || parent[y] == x) {
      currentVal = (currentVal + val)%MOD;
    }
  }

  pendingUpdates.push_back({x, currentVal});

  if (pendingUpdates.size() == THRESHOLD) {
    applyPendingUpdates();
  }
}

LL query(int x) {
  LL currentAns = ans[x];
  int numNeighborsOfX = (int) adj[x].size();
  for (auto [y, val]: pendingUpdates) {
    if (y == x) {
      currentAns = (currentAns + ((LL) val * numNeighborsOfX)%MOD)%MOD;
    } else if ((parent[y] != -1 && parent[parent[y]] == x) || (parent[x] != -1 && parent[parent[x]] == y) || (parent[x] == parent[y])) {
      currentAns = (currentAns + val)%MOD;
    }
  }

  return currentAns;
}

int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
  }

  for (int i = 1; i < N; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  memset(parent, -1, sizeof(parent));
  dfs(1);

  applyPendingUpdates();

  scanf("%d", &Q);
  for (int i = 1; i <= Q; i++) {
    int T, X;
    scanf("%d%d", &T, &X);

    if (T == 1) {
      update(X);
    } else {
      printf("%lld\n", query(X));
    }
  }
}
