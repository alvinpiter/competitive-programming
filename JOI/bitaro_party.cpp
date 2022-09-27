/*
2018 JOI Spring Training Camp/Qualifying Trial Day 3

There are two ways to solve this problem, and we need to combine them:
* In O(N), by using dynamic programming. dp[i] -> maximum number of jumps to reach destination from node i.
* (N + M)*THRESHOLD, by precomputation. For each node, we store the top THRESHOLD furthest nodes from it.

We solve the problem with the first approach whenever the Y is >= THRESHOLD. When doing so, the total complexity
for answering all queries will be (N/THRESHOLD)*N.

If Y < THRESHOLD, then we can use our precomputed value since we store the top THRESHOLD nodes from each node. Which means
at least one of them is able to attend the party.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define THRESHOLD 120

int N, M, Q, T, Y, C[MAXN + 3], canGo[MAXN + 3], dp[MAXN + 3];
bool seen[MAXN + 3];
vector<int> nxt[MAXN + 3];
vector<pair<int, int> > best[MAXN + 3]; // best[u] -> [ {numJump, who} ], means we can reach "u" from "who" with "numJump" jumps.

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

  cin >> N >> M >> Q;
  for (int i = 1; i <= M; i++) {
    int s, e;
    cin >> s >> e;

    nxt[s].push_back(e);
  }

  for (int i = 1; i <= N; i++) {
    canGo[i] = true;
  }

  for (int i = 1; i <= N; i++) {
    best[i].push_back({0, i});
  }

  memset(seen, false, sizeof(seen));
  for (int i = 1; i <= N; i++) {
    sort(best[i].rbegin(), best[i].rend());

    vector<pair<int, int> > temp;
    for (auto [numJump, who]: best[i]) {
      if (seen[who]) {
        continue;
      }

      seen[who] = true;
      temp.push_back({numJump, who});
      if (temp.size() == THRESHOLD) {
        break;
      }
    }

    swap(best[i], temp);

    for (auto [numJump, who]: best[i]) {
      seen[who] = false; // Not the best place to reset this value lol.
      for (auto k: nxt[i]) {
        best[k].push_back({numJump + 1, who});
      }
    }
  }

  for (int q = 1; q <= Q; q++) {
    cin >> T >> Y;
    for (int i = 1; i <= Y; i++) {
      cin >> C[i];
      canGo[C[i]] = false;
    }

    if (Y >= THRESHOLD) {
      dp[T] = 0;
      for (int i = T - 1; i >= 1; i--) {
        dp[i] = -1;
        for (auto j: nxt[i]) {
          if (j <= T && dp[j] != -1) {
            dp[i] = max(dp[i], 1 + dp[j]);
          }
        }
      }

      int ans = -1;
      for (int i = 1; i <= T; i++) {
        if (canGo[i] && dp[i] != -1) {
          ans = max(ans, dp[i]);
        }
      }

      cout << ans << endl;
    } else {
      int ans = -1;
      for (auto [numJump, who]: best[T]) {
        if (canGo[who]) {
          ans = max(ans, numJump);
        }
      }

      cout << ans << endl;
    }

    // Reset
    for (int i = 1; i <= Y; i++) {
      canGo[C[i]] = true;
    }
  }
}
