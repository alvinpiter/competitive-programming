/*
Imagine 3 points, (x1, y1), (x2, y2), (x3, y3) where x1 <= x2 <= x3 and y2 = y3.

It's obvious that d12 < d13 and d23 < d13. Whenever we run Kruskal's algorithm,
d13 will never be part of the MST edge, because once we have processed d12 and d23,
all the three points are already connected.

With the above observation, we can see that the number of "important" edges is quite small, i.e at most 11N.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int n, parent[MAXN + 3], x[MAXN + 3], y[MAXN + 3];
vector<pair<int, int> > pointsAtY[11]; // {x, index}
vector<pair<LL, pair<int, int> > > edges;

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

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
    pointsAtY[y[i]].push_back(make_pair(x[i], i));
  }

  for (int y = 0; y <= 10; y++) {
    sort(pointsAtY[y].begin(), pointsAtY[y].end());
  }

  for (int i = 1; i <= n; i++) {
    for (int ye = 0; ye <= 10; ye++) {
      int lb = lower_bound(pointsAtY[ye].begin(), pointsAtY[ye].end(), make_pair(x[i] + (y[i] == ye ? 1 : 0), 0)) - pointsAtY[ye].begin();
      if (lb < pointsAtY[ye].size()) {
        int j = pointsAtY[ye][lb].second;
        LL dist = (LL) (x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j]);
        edges.push_back(make_pair(dist, make_pair(i, j)));
      }
    }
  }

  sort(edges.begin(), edges.end());

  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }

  LL mst = 0;
  for (int i = 0; i < edges.size(); i++) {
    pair<LL, pair<int, int> > edge = edges[i];
    LL cost = edge.first;
    int u = edge.second.first, v = edge.second.second;

    if (!isSameSet(u, v)) {
      mst += cost;
      joinSet(u, v);
    }
  }

  cout << mst << endl;
}
