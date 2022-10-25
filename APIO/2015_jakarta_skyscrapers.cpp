/*
Observation: In an optimal solution, each doge should only be used once.

With the above observation, we can construct a solution using state graph, where the state
are the position of the message and the power of the doge holding the message.
The state: (position, power).

For each position, define an "entry" vertex for that position. The entry vertex is useful
for transitioning from another position to the current position without worrying about the power of
the doge. Vertices (position, 0) will be designated as "entry" vertex.

Graph construction:
* Define a power threshold, THRESHOLD.
* From each entry vertices (position, 0), we can go to:
  * (position, power), where power <= THRESHOLD
  * (position', 0), where position' is the position after taking jumps using doge with power > THRESHOLD.
* From vertex (position, power > 0), we can go to:
  * (position + power, power) or (position + power, 0)
  * (position - power, power) or (position - power, 0)

Number of vertices: N * THRESHOLD
Number edges:
* Edges originating from (position, power > 0) -> only 4 edges for each vertices. Total: 4 * N * THRESHOLD
* Edges originating from (position, power = 0) -> (nSmall[0] + .. + nSmall[n - 1]) + (nLarge[0] + .. + nLarge[n - 1]) * N/THRESHOLD
                                               -> <= M + M * N/THRESHOLD

nSmall[i] and nLarge[i] is the number of doges whose power is <= THRESHOLD and > THRESHOLD respectively.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 30000
#define THRESHOLD 180

int n, m, startPosition, endPosition, dist[MAXN + 3][THRESHOLD + 3];
vector<int> dogesAtPosition[MAXN + 3];

int main() {
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int b, p;
    cin >> b >> p;

    if (i == 0) {
      startPosition = b;
    }

    if (i == 1) {
      endPosition = b;
    }

    dogesAtPosition[b].push_back(p);
  }

  for (int i = 0; i < n; i++) {
    sort(dogesAtPosition[i].begin(), dogesAtPosition[i].end());
    dogesAtPosition[i].erase(unique(dogesAtPosition[i].begin(), dogesAtPosition[i].end()), dogesAtPosition[i].end());
  }

  for (int i = 0; i < n; i++) {
    for (int p = 0; p <= THRESHOLD; p++) {
      dist[i][p] = INF;
    }
  }
  dist[startPosition][0] = 0;

  priority_queue<pair<int, pair<int, int> > > pq;
  pq.push({-dist[startPosition][0], {startPosition, 0}});

  while (!pq.empty()) {
    auto [d, state] = pq.top(); pq.pop();
    auto [position, power] = state;

    d *= -1; // Because we push -dist
    if (d > dist[position][power]) {
      continue;
    }

    if (power == 0) {
      for (auto newPower: dogesAtPosition[position]) {
        if (newPower <= THRESHOLD) {
          if (dist[position][newPower] > dist[position][power]) {
            dist[position][newPower] = dist[position][power];
            pq.push({-dist[position][newPower], {position, newPower}});
          }
        } else {
          for (int direction = -1; direction <= 1; direction += 2) {
            for (int numJumps = 1; ; numJumps++) {
              int newPosition = position + direction * newPower * numJumps;
              if (newPosition < 0 || newPosition >= n) {
                break;
              }

              if (dist[newPosition][0] > dist[position][power] + numJumps) {
                dist[newPosition][0] = dist[position][power] + numJumps;
                pq.push({-dist[newPosition][0], {newPosition, 0}});
              }
            }
          }
        }
      }
    } else {
      for (int direction = -1; direction <= 1; direction += 2) {
        int newPosition = position + direction * power;
        if (newPosition >= 0 && newPosition < n) {
          if (dist[newPosition][0] > dist[position][power] + 1) {
            dist[newPosition][0] = dist[position][power] + 1;
            pq.push({-dist[newPosition][0], {newPosition, 0}});
          }

          if (dist[newPosition][power] > dist[position][power] + 1) {
            dist[newPosition][power] = dist[position][power] + 1;
            pq.push({-dist[newPosition][power], {newPosition, power}});
          }
        }
      }
    }
  }

  int ans = INF;
  for (int p = 0; p <= THRESHOLD; p++) {
    ans = min(ans, dist[endPosition][p]);
  }

  if (ans < INF) {
    cout << ans << endl;
  } else {
    cout << -1 << endl;
  }
}
