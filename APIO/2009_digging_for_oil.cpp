/*
Possible configurations of the 3 sub-rectangles:
* 1 before a column c, 2 after column c.
  * The two rectangles after column c can be "on top of each other" or
    "next to each other".
* 1 after a column c, 2 before column c.
* 1 before a row r, 2 after row r.
* 1 after a row r, 2 before row r.

We will just solve the first 2 configurations, and then rotate the input matrix
to solve the last 2 configurations.

bestTopLeft[i][j] -> Best sub-rectangles which is completely in the top left quadrant.
bestTopRight, bestBottomLeft, bestBottomRight are defined similarly.

bestEndingAtColumn[j] -> best sub-rectangles whose right end ends at column j.
bestBetweenColumn[j1][j2] -> best sub-rectangles which is completely in between column j1 and j2.

bestEndingAtColumn[j] is used for calculating bestBetweenColumn[j1][j2].
*/


#include<bits/stdc++.h>
using namespace std;
#define MAXN 1500

int R, C, K, mat[MAXN + 3][MAXN + 3], temp[MAXN + 3][MAXN + 3];
int psum[MAXN + 3][MAXN + 3];
int bestTopLeft[MAXN + 3][MAXN + 3], bestTopRight[MAXN + 3][MAXN + 3], bestBottomLeft[MAXN + 3][MAXN + 3], bestBottomRight[MAXN + 3][MAXN + 3];
int bestEndingAtColumn[MAXN + 3], bestBetweenColumn[MAXN + 3][MAXN + 3];

int querySum(int r1, int c1, int r2, int c2) {
  if (r1 > r2 || c1 > c2) return 0;
  r1 = max(r1, 1);
  c1 = max(c1, 1);
  r2 = min(r2, R);
  c2 = min(c2, C);

  return psum[r2][c2] - psum[r2][c1 - 1] - psum[r1 - 1][c2] + psum[r1 - 1][c1 - 1];
}

int solve() {
  memset(psum, 0, sizeof(psum));
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      psum[i][j] = mat[i][j] + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
    }
  }

  memset(bestTopLeft, 0, sizeof(bestTopLeft));
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      bestTopLeft[i][j] = max(max(bestTopLeft[i - 1][j], bestTopLeft[i][j - 1]), max(bestTopLeft[i - 1][j - 1], querySum(i - K + 1, j - K + 1, i, j)));
    }
  }

  memset(bestTopRight, 0, sizeof(bestTopRight));
  for (int i = 1; i <= R; i++) {
    for (int j = C; j >= 1; j--) {
      bestTopRight[i][j] = max(max(bestTopRight[i - 1][j], bestTopRight[i][j + 1]), max(bestTopRight[i - 1][j + 1], querySum(i - K + 1, j, i, j + K - 1)));
    }
  }

  memset(bestBottomLeft, 0, sizeof(bestBottomLeft));
  for (int i = R; i >= 1; i--) {
    for (int j = 1; j <= C; j++) {
      bestBottomLeft[i][j] = max(max(bestBottomLeft[i + 1][j], bestBottomLeft[i][j - 1]), max(bestBottomLeft[i + 1][j - 1], querySum(i, j - K + 1, i + K - 1, j)));
    }
  }

  memset(bestBottomRight, 0, sizeof(bestBottomRight));
  for (int i = R; i >= 1; i--) {
    for (int j = C; j >= 1; j--) {
      bestBottomRight[i][j] = max(max(bestBottomRight[i + 1][j], bestBottomRight[i][j + 1]), max(bestBottomRight[i + 1][j + 1], querySum(i, j, i + K - 1, j + K - 1)));
    }
  }

  memset(bestEndingAtColumn, 0, sizeof(bestEndingAtColumn));
  for (int j = 1; j <= C; j++) {
    for (int i = 1; i <= R; i++) {
      bestEndingAtColumn[j] = max(bestEndingAtColumn[j], querySum(i - K + 1, j - K + 1, i, j));
    }
  }

  memset(bestBetweenColumn, 0, sizeof(bestBetweenColumn));
  for (int j1 = 1; j1 <= C; j1++) {
    for (int j2 = j1 + K - 1; j2 <= C; j2++) {
      bestBetweenColumn[j1][j2] = max(bestBetweenColumn[j1][j2 - 1], bestEndingAtColumn[j2]);
    }
  }

  int best = 0;
  for (int j = 1; j <= C; j++) {
    for (int i = 1; i <= R; i++) {
      // 1 rectangle to the left of column j, 2 rectangles to the right
      best = max(best, bestTopLeft[R][j] + bestTopRight[i][j + 1] + bestBottomRight[i + 1][j + 1]);

      // 2 rectangles to the left of column j, 1 rectangle to the right
      best = max(best, bestTopLeft[i][j] + bestBottomLeft[i + 1][j] + bestTopRight[R][j + 1]);
    }
  }

  for (int j1 = 1; j1 <= C; j1++) {
    for (int j2 = j1 + K; j2 <= C; j2++) {
      // 1 rectangle before column j1, 1 between j1 and j2, 1 after j2
      best = max(best, bestTopLeft[R][j1] + bestBetweenColumn[j1 + 1][j2] + bestTopRight[R][j2 + 1]);
    }
  }

  return best;
}

int main() {
  scanf("%d%d%d", &R, &C, &K);
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      scanf("%d", &mat[i][j]);
      temp[j][i] = mat[i][j];
    }
  }

  int ans = solve();

  swap(R, C);
  for (int i = 1; i <= R; i++) {
    for (int j = 1; j <= C; j++) {
      mat[i][j] = temp[i][j];
    }
  }

  ans = max(ans, solve());

  printf("%d\n", ans);
}
