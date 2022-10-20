/*
Let's sort the trapezoid by its top-left coordinate, in increasing order.

Define:
dp[i] = The size of max independent set of trapezoids that can be formed using the i-th trapezoid upto the last
trapezoid, and the i-th trapezoid is included in the set.

dp[i] = max(1 + dp[j]), where the j-th (j > i) trapezoid doesn't intersect with the i-th trapezoid.

Naive implementation will take O(N^2) time. The bottleneck of the solution is in finding the trapezoid
that doesn't intersect with the current trapezoid.

To speed up the solution, we need a data structure that can support the following queries:
* Get the value of dp[j] (and number of ways to achieve it) for all trapezoids whose lower-left corner is larger than
  a certain value.
* Insert the value of dp[j] for a trapezoid whose lower-left corner is a certain value.

We have to be careful when dealing with the above data structure. We only insert trapezoids whose top-left corner is larger
than the current trapezoid's top-right corner. This can be ensured by processing the top points of the trapezoids from the
right most one. Whenever we encounter a top-right corner, we query, and whenever we encounter a top-left corner, we insert.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXV 400001
#define MAXN 100000
#define MOD 30013

int n, t[MAXN + 3][4], topPointOwner[MAXV + 3], dp[MAXN + 3], numWays[MAXN + 3];
bool isTopLeftPoint[MAXV + 3];
vector<int> uniqueCoordinates;
pair<int, int> tree[4 * MAXV + 3];

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
  if (a.first != b.first) {
    return a.first < b.first ? b : a;
  } else {
    return make_pair(a.first, (a.second + b.second)%MOD);
  }
}

void doUpdate(int node, int l, int r, int idx, int sz, int ways) {
  if (r < idx || l > idx) {
    return;
  }

  if (l == r) {
    tree[node] = {sz, ways};
    return;
  }

  int m = (l + r)/2;
  doUpdate(2 * node, l, m, idx, sz, ways);
  doUpdate(2 * node + 1, m + 1, r, idx, sz, ways);

  tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

void update(int idx, int sz, int ways) {
  doUpdate(1, 1, MAXV, idx, sz, ways);
}

pair<int, int> doQuery(int node, int l, int r, int ql, int qr) {
  if (r < ql || l > qr) {
    return {0, 0};
  }

  if (l >= ql && r <= qr) {
    return tree[node];
  }

  int m = (l + r)/2;
  return combine(doQuery(2 * node, l, m, ql, qr), doQuery(2 * node + 1, m + 1, r, ql, qr));
}

pair<int, int> query(int idx) {
  return doQuery(1, 1, MAXV, idx, MAXV);
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++) {
      cin >> t[i][j];
      uniqueCoordinates.push_back(t[i][j]);
    }
  }

  sort(uniqueCoordinates.begin(), uniqueCoordinates.end());
  uniqueCoordinates.erase(unique(uniqueCoordinates.begin(), uniqueCoordinates.end()), uniqueCoordinates.end());

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 4; j++) {
      t[i][j] = (lower_bound(uniqueCoordinates.begin(), uniqueCoordinates.end(), t[i][j]) - uniqueCoordinates.begin()) + 1;
    }
  }

  memset(topPointOwner, -1, sizeof(topPointOwner));
  memset(isTopLeftPoint, false, sizeof(isTopLeftPoint));
  for (int i = 1; i <= n; i++) {
    topPointOwner[t[i][0]] = topPointOwner[t[i][1]] = i;
    isTopLeftPoint[t[i][0]] = true;
  }

  for (int c = 1; c <= 4 * MAXV; c++) {
    tree[c] = {0, 0};
  }
  update(MAXV, 0, 1);

  for (int c = MAXV - 1; c >= 1; c--) {
    if (topPointOwner[c] == -1) {
      continue;
    }

    int owner = topPointOwner[c];

    if (isTopLeftPoint[c]) {
      update(t[owner][2], dp[owner], numWays[owner]);
    } else {
      auto queryResult = query(t[owner][3] + 1);
      dp[owner] = 1 + queryResult.first;
      numWays[owner] = queryResult.second;
    }
  }

  pair<int, int> ans = {0, 0};
  for (int i = 1; i <= n; i++) {
    ans = combine(ans, {dp[i], numWays[i]});
  }

  cout << ans.first << " " << ans.second << endl;
}
