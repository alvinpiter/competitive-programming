/*
Imagine adding the schools one by one starting from the first upto the last.
If after adding f schools all students are already assigned to a school, then
we are done. The value of f can be binary-searched. For each value of f, we
run Dijkstra's algorithm from the first f schools. If there is a student whose
distance is larger than its threshold, then we need to add more schools. Otherwise,
we can decrease f.

Once we found f, we again run Dijkstra's algorithm from the first (f - 1) schools.
Any students that are not assigned to any school are assigned to k-th school.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100000
#define MAXK 100000

int N, M, K, P[MAXK + 3], A[MAXK + 3], dist[MAXN + 3];
vector<pair<int, int> > adj[MAXN + 3];

// Run Dijkstra's algorithm from the first f schools.
void Dijkstra(int f) {
  for (int i = 1; i <= f; i++) {
    adj[0].push_back({i, 0});
  }

  dist[0] = 0;
  for (int i = 1; i <= N; i++) {
    dist[i] = INF;
  }

  priority_queue<pair<int, int> > pq;
  pq.push({-dist[0], 0});

  while (!pq.empty()) {
    auto top = pq.top(); pq.pop();
    auto [d, u] = top;

    d *= -1;
    if (d > dist[u]) {
      continue;
    }

    for (auto [v, w]: adj[u]) {
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        pq.push({-dist[v], v});
      }
    }
  }

  adj[0].clear();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> N >> M;
  for (int i = 1; i <= M; i++) {
    int u, v, w;
    cin >> u >> v >> w;

    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  cin >> K;
  for (int i = 1; i <= K; i++) {
    cin >> P[i] >> A[i];
  }

  int lo = 1, hi = N, mid;
  while (hi >= lo) {
    mid = (lo + hi)/2;

    Dijkstra(mid);
    bool anyUnpairedStudent = false;
    for (int i = 1; i <= K; i++) {
      if (dist[P[i]] > A[i]) {
        anyUnpairedStudent = true;
      }
    }

    if (anyUnpairedStudent) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  // lo is the maximum index of the schools which have at least 1 student.
  Dijkstra(lo - 1);

  int ans = -1;
  for (int i = 1; i <= K; i++) {
    if (dist[P[i]] > A[i]) {
      ans = i;
    }
  }

  cout << ans << endl;
}
