/*
If the beetle collects c drops of water on time t1, t2, ..., tc respectively, the total amount of drank
water is (m - t1) + (m - t2) + ... + (m - tc) = c * m - (t1 + t2 + ... + tc).

For a particular c, we must minimize the sum of collection times t1 + t2 + .. + tc. We can do this with
dynamic programming:

dp[l][r][isAtL][c] -> the minimal total time to collect c drops of water if the drops from
index l to r (inclusive) is already collected and the beetle is currently at l/r.

dp[l][r][0][c] = min(dp[l - 1][r][1][c - 1] + (x[l] - x[l - 1]) * c, dp[l][r + 1][0][c - 1] + (x[r + 1] - x[l]) * c)

Notice that the distance is multiplied by c. This is because every unit we move, all c of our drops decreases its amount of
water by 1 unit.

The answer is max(m * c - dp[start][start][0][c]), across all possible c.
"start" is the starting position, i.e the one with x = 0.

Possible edge case:
* There is a drop of water located at x = 0.
* n = 0
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 300

int n, m, dp[MAXN + 3][MAXN + 3][2][MAXN + 3];
vector<int> xs;

int getMinTime(int l, int r, int isAtL, int c) {
  if (c == 0) {
    return 0;
  }

  if (dp[l][r][isAtL][c] != -1) {
    return dp[l][r][isAtL][c];
  }

  int best = INF;

  // Try reaching l - 1 if possible
  if (l > 0) {
    int dist = (isAtL == 1 ? xs[l] - xs[l - 1] : xs[r] - xs[l - 1]);
    best = min(best, c * dist + getMinTime(l - 1, r, 1, c - 1));
  }

  // Try reaching r + 1 if possible
  if (r + 1 < xs.size()) {
    int dist = (isAtL == 1 ? xs[r + 1] - xs[l] : xs[r + 1] - xs[r]);
    best = min(best, c * dist + getMinTime(l, r + 1, 0, c - 1));
  }

  return dp[l][r][isAtL][c] = best;
}

int main() {
  cin >> n >> m;

  bool zeroExists = false;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (x == 0) {
      zeroExists = true;
    }

    xs.push_back(x);
  }

  if (!zeroExists) {
    xs.push_back(0);
  }

  sort(xs.begin(), xs.end());

  int startingPosition;
  for (int i = 0; i < xs.size(); i++) {
    if (xs[i] == 0) {
      startingPosition = i;
      break;
    }
  }

  memset(dp, -1, sizeof(dp));

  int ans = 0;
  for (int c = 1; c <= n; c++) {
    ans = max(ans, m * c - getMinTime(startingPosition, startingPosition, 0, c));
  }

  cout << ans + (zeroExists ? m : 0) << endl;
}
