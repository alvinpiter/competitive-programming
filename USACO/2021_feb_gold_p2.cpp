/*
Thought process:
Draw segments to connect two points that are last painted by a same stroke. Notice that these segments can't intercept
with each other, but one segment can be fully enclosed by another segment.

Define:
* numSegments[i] as the number of segments created by i-th stroke.
* numAffectedPoints[i] as the number of points which is last stroke by i-th stroke.

The following condition holds:
numSegments[i] = numAffectedPoints[i] - 1.

Hence:
Total number of segments = N - k, where k is the number of strokes.

To minimize k, we must maximize total number of segments. The segments must fulfill the following condition:
* Start and ends at the same color
* Covers at least 2 points
* Can't intercept, but able to be fully enclosed by another segment.

This can be calculated by dynamic programming.
dp[i][j] -> maximum number of segments from index i to index j.

Test cases:
7
1 3 2 3 1 2 1
Output should be 4

9
1 3 2 3 1 2 1 2 1
Output should be 5
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 300

int n, color[MAXN + 3], dp[MAXN + 3][MAXN + 3];

int solve(int i, int j) {
  if (i >= j) {
    return 0;
  }

  if (dp[i][j] != -1) {
    return dp[i][j];
  }

  int maxi = solve(i + 1, j);
  for (int k = i + 1; k <= j; k++) {
    if (color[i] == color[k]) {
      maxi = max(maxi, 1 + solve(i + 1, k - 1) + solve(k, j));
    }
  }

  return dp[i][j] = maxi;
}

int main() {

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> color[i];
  }

  memset(dp, -1, sizeof(dp));
  cout << n - solve(1, n) << endl;
}
