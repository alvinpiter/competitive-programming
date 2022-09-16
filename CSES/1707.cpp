/*
For each edge a-b:
* Remove this edge.
* Find the shortest distance from a to b, let's say it's d. The cycle involving a and b has length d + 1.

Find minimal d.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000

int main() {
  int n, m, e1[5003], e2[5003], dist[2503];
  vector<int> adj[2503];

  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e1[i] >> e2[i];
    adj[e1[i]].push_back(e2[i]);
    adj[e2[i]].push_back(e1[i]);
  }

  int ans = INF;
  for (int i = 1; i <= m; i++) {
    memset(dist, -1, sizeof(dist));

    queue<int> q;
    dist[e1[i]] = 0;
    q.push(e1[i]);

    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int j = 0; j < adj[u].size(); j++) {
        int v = adj[u][j];

        if (u == e1[i] && v == e2[i]) {
          continue;
        }

        if (u == e2[i] && v == e1[i]) {
          continue;
        }

        if (dist[v] == -1) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }

    if (dist[e2[i]] != -1) {
      ans = min(ans, dist[e2[i]] + 1);
    }
  }

  if (ans < INF) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
}
