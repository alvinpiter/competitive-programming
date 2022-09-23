/*
Imagine there are 2P + 2 points on the plane:
* 2P points are the endpoints of the springboard
* 1 point is the origin, (0, 0)
* 1 point is the destination, (N, N)

From each point, we'd like to know the minimal number of walks needed to reach (N, N).
Assume we are currently at point i, then we have a few options:
* Walk to another point j. The total cost would be: (xj + yj + minWalk(j)) - (xi + yi)
* If the current point is the starting point of a springboard, we can jump to the ending point.

New data structure, static suffix min. The DS should support:
* Adding a key-value (k, v)
* Query minimal value for keys that are >= k

How it works:
Maintain the values in increasing order, i.e (k1, v1), (k2, v2), ... must fulfill
k1 < k2 < k3
v1 < v2 < v3

When adding a key-value, maintain the above property.
When query a key, just do lower bound.
*/

#include<bits/stdc++.h>
using namespace std;

int n, p, ans[100003];
vector<pair<pair<int, int>, pair<int, int> > > events; // {point, { idx, -1/1 }}
map<int, int> suffixMap; // {y, x + y + min_walk_to_destination}

void insert(int y, int val) {
  map<int, int>::iterator lb = suffixMap.lower_bound(y);
  if (lb != suffixMap.end() && lb->second <= val) {
    return;
  }

  suffixMap[y] = val;
  while (true) {
    map<int, int>::iterator loc = suffixMap.lower_bound(y);
    if (loc != suffixMap.begin() && prev(loc)->second >= val) {
      suffixMap.erase(prev(loc));
    } else {
      break;
    }
  }
}

int query(int y) {
  map<int, int>::iterator lb = suffixMap.lower_bound(y);
  return lb->second;
}

int main() {
  freopen("boards.in", "r", stdin);
  freopen("boards.out", "w", stdout);

  cin >> n >> p;
  for (int i = 0; i < p; i++) {
    pair<int, int> p1, p2;
    cin >> p1.first >> p1.second >> p2.first >> p2.second;

    events.push_back(make_pair(p1, make_pair(i, -1)));
    events.push_back(make_pair(p2, make_pair(i, 1)));
  }

  sort(events.begin(), events.end());

  insert(n, 2*n);
  for (int i = events.size() - 1; i >= 0; i--) {
    pair<int, int> p = events[i].first;
    pair<int, int> extra = events[i].second;

    if (extra.second == 1) {
      ans[extra.first] = query(p.second) - p.first - p.second;
    } else {
      insert(p.second, ans[extra.first] + p.first + p.second);
    }
  }

  cout << query(0) << endl;
}
