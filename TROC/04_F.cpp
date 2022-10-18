/*
Solving the queries online:
The answer must be one of the divisor of gcd(A, B). Let's say we'd like to check if D is one of the answer candidates.
We do the following:

Let G[D] is a subgraph of the original graph such that:
* The nodes are the same with the original graph.
* The edges are the subset of the edges of the original graph where edge (u, v) in the original graph
  is included iff both u and v are divisible by D.

If A and B are connected in D, then D is one of the answer candidates.

Building the graph takes O(M) time, and checking for each possible D takes O(sqrt(A)), hence the total complexity
per query is O(M * sqrt(A)). This will get TLE.

One possible optimization is by processing the queries in batch, i.e we'd like to answer all the queries where D is one of
its answer candidates. Look at the comments to understand the total complexity.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXA 100000
#define MAXN 100000

int n, m, q, w[MAXN + 3], parent[MAXN + 3], ans[MAXN + 3];
vector<int> divisors[MAXA + 3];
vector<pair<int, int> > edges[MAXA + 3];
vector<pair<int, pair<int, int> > > queries[MAXA + 3];

int findParent(int i) {
  return parent[i] == i ? i : parent[i] = findParent(parent[i]);
}

bool isSameSet(int i, int j) {
  return findParent(i) == findParent(j);
}

void joinSet(int i, int j) {
  parent[findParent(i)] = findParent(j);
}

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a%b);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

  for (int i = 1; i <= MAXA; i++) {
    for (int j = i; j <= MAXA; j += i) {
      divisors[j].push_back(i);
    }
  }

  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }

  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;

    for (auto d: divisors[gcd(w[u], w[v])]) {
      edges[d].push_back({u, v});
    }
  }

  cin >> q;
  for (int i = 1; i <= q; i++) {
    int a, b;
    cin >> a >> b;

    for (auto d: divisors[gcd(w[a], w[b])]) {
      queries[d].push_back({i, {a, b}});
    }
  }

  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }

  for (int d = 1; d <= MAXA; d++) {
    if (queries[d].empty()) continue;

    /*
    For a particular d, there are at most MAXA/d nodes to be joined.
    Hence the total number of times joinSet is called is MAXA + MAXA/2 + MAXA/3 + ... 1 = MAXA * log(MAXA)
    */
    for (auto edge: edges[d]) {
      joinSet(edge.first, edge.second);
    }

    /*
    The complexity of the following loops are the same with the previous.
    */

    for (auto query: queries[d]) {
      if (isSameSet(query.second.first, query.second.second)) {
        ans[query.first] = d;
      }
    }

    for (auto edge: edges[d]) {
      parent[edge.first] = edge.first;
      parent[edge.second] = edge.second;
    }
  }

  for (int i = 1; i <= q; i++) {
    cout << ans[i] << endl;
  }
}
