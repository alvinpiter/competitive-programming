/*
Assume our X-axis goes from left to right, and our Y-axis goes from top top bottom.

We will solve this problem using Kruskal's algorithm.

Observation:
Imagine there are 2 points (x1, y1) and (x2, y2), where x1 = x2 and y1 < y2. We'd like to connect
these points to the points to the right of them, i.e whose x > x1. The edge from (x2, y2) to (x3, y3), where
y3 <= y1, will never contribute to the answer. Reason: dist(1, 2) < dist(2, 3) and dist(1, 3) < dist(2, 3), therefore
, after processing edges 1-2 and 1-3, 1-2-3 will already be connected.

Another observation:
If we have connected (x, y) to (x1, y1), x1 >= x, then the edge from (x, y) to (x2, y2), where x2 > x1 and
y2 = y1 will not contribute to the answer. The reason is quite similar with the previous observation.

With the above observations the number of edges we need to consider is not too many. The total number of edges which
starts from a point with certain x coordinate is at most 2000. Since there are at most 1000 different x coordinates,
the total edges to be considered is aroud 2x10^6.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXX 1000

int n, x[MAXN + 3], y[MAXN + 3];
int parent[MAXN + 3];

int findParent(int u) {
  if (parent[u] == u) {
    return u;
  } else {
    return parent[u] = findParent(parent[u]);
  }
}

bool isSameSet(int u, int v) {
  return findParent(u) == findParent(v);
}

void joinSet(int u, int v) {
  parent[findParent(u)] = findParent(v);
}

int manhattan(int u, int v) {
  return abs(x[u] - x[v]) + abs(y[u] - y[v]);
}

int mst(vector<pair<int, pair<int, int > > > edges) {
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }

  sort(edges.begin(), edges.end());

  int mst = 0;
  for (auto edge: edges) {
    int cost = edge.first;
    auto [u, v] = edge.second;

    if (!isSameSet(u, v)) {
      mst += cost;
      joinSet(u, v);
    }
  }

  return mst;
}

int solve() {
  vector<pair<int, int> > whoAtX[MAXX + 3];
  set<pair<int, int> > whoAtY[MAXX + 3];

  for (int i = 1; i <= n; i++) {
    whoAtX[x[i]].push_back({y[i], i});
    whoAtY[y[i]].insert({x[i], i});
  }

  vector<pair<int, pair<int, int> > > edges;

  // Building the graph
  for (int x = 0; x <= MAXX; x++) {
    sort(whoAtX[x].begin(), whoAtX[x].end());

    // Remove obsolete points
    for (int y = 0; y <= MAXX; y++) {
      while (!whoAtY[y].empty() && whoAtY[y].begin()->first <= x) {
        whoAtY[y].erase(whoAtY[y].begin());
      }
    }

    int minY = 0;
    for (int i = 0; i < whoAtX[x].size(); i++) {
      int maxY = (i == whoAtX[x].size() - 1 ? MAXX : y[whoAtX[x][i + 1].second] - 1);

      // Connect to previous point on the same column
      if (i > 0) {
        int u = whoAtX[x][i].second, v = whoAtX[x][i - 1].second;
        edges.push_back({manhattan(u, v), {u, v}});
      }

      // Connect to points whose y coordinate is between minY and maxY
      for (int y = minY; y <= maxY; y++) {
        if (!whoAtY[y].empty()) {
          int u = whoAtX[x][i].second, v = whoAtY[y].begin()->second;
          edges.push_back({manhattan(u, v), {u, v}});
        }
      }

      minY = y[whoAtX[x][i].second];
    }
  }

  return mst(edges);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
  }

  cout << solve() << endl;
}
