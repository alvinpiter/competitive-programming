/*
Assume we'd like to know whether it is possible to achieve partition value to be at least P.
To make the partition value to be at least P, two people whose amiability is < P can't be put
in the same group. Let's build a graph where each vertex represents a person and two people
are connected with an edge iff their amiability is < P. If there is an odd-length cycle in this
graph, then we can't have partition value to be at least P.

The maximum value of P is binary-searchable, because if there is no odd-length cycle in the graph with
threshold P, then there is no odd-length cycle in the graph with threshold (P - 1). This is because
the number of edges is smaller.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 500

int n, a[MAXN + 3][MAXN + 3], dfsNum[MAXN + 3], dist[MAXN + 3];
bool anyOddLengthCycle;

void dfs(int u, int threshold) {
  dfsNum[u] = 1;
  for (int v = 1; v <= n; v++) {
    if (v == u || dfsNum[v] == 2 || a[u][v] >= threshold) continue;

    if (dfsNum[v] == 1) {
      int cycleLength = dist[u] - dist[v] + 1;
      if (cycleLength % 2 == 1) {
        anyOddLengthCycle = true;
      }
      continue;
    }

    if (dfsNum[v] == -1) {
      dist[v] = dist[u] + 1;
      dfs(v, threshold);
    }
  }

  dfsNum[u] = 2;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
    }
  }

  int lo = 0, hi = 1000000001, mid;
  while (hi >= lo) {
    mid = (lo + hi)/2;

    memset(dfsNum, -1, sizeof(dfsNum));
    anyOddLengthCycle = false;

    for (int i = 1; i <= n; i++) {
      if (dfsNum[i] == -1) {
        dist[i] = 0;
        dfs(i, mid);
      }
    }

    if (anyOddLengthCycle) {
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }

  cout << hi << endl;
}
