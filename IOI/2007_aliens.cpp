/*
Subproblem:
Given some 1xN blocks which are put next to each other and the blocks are colored alternatingly, i.e
the first block is colored black, then the second block is colored white, and so on.

Given the position of one of the black cell. Find the position of its block's right end and left end.

To find the right end, we can do so by querying:
x + 2^0, x + 2^1, x + 2^2, and so on. Once we have found the first white cell, the found white cell's block must be the block
next to x's block. Proof: Assume x + 2^p is the coordinate with the last black cell, which means the coordinate x + 2^(p + 1)
contains white cell. We know that x + 2^p <= currentBlockRightEnd, hence x + 2^(p + 1) <= currentBlockRightEnd + (currentBlockRightEnd - x).

Since currentBlockRightEnd - x < N, then x + 2^(p + 1) < currentBlockRightEnd + N. This implies x + 2^(p + 1) belongs to
the next block.

Because we have found 2 consecutive blocks, we can now perform binary search.
*/

#include<bits/stdc++.h>
using namespace std;
/*
(ex0, ye0) -> Given coordinate with flatten grass
(ex1, ye1) -> The lower-left coordinate of the block where (ex0, ye0) belongs to
(ex2, ye2) -> The lower-left coordinate of the whole structure
*/
int n, m, ex0, ye0, ex1, ye1, ex2, ye2;
int smallestJumpToUnflattenedInDirection[4];

int testingMatrix[100][100];

// up, right, down, left
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool isInsideGrid(int x, int y) {
  return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool examine(int x, int y) {
  if (!isInsideGrid(x, y)) {
    return false;
  }

  cout << "examine " << x << " " << y << endl;
  cout << flush;

  string response;
  cin >> response;

  return response == "true";
}

void solution(int x, int y) {
  cout << "solution " << x << " " << y << endl;
  cout << flush;
}

void solve() {
  for (int direction = 0; direction < 4; direction++) {
    int threshold;
    for (int p2 = 1; ; p2 *= 2) {
      int x = ex0 + p2 * dx[direction], y = ye0 + p2 * dy[direction];
      if (examine(x, y) == false) {
        threshold = p2;
        break;
      }
    }

    int lo = 1, hi = threshold, mid;
    while (hi >= lo) {
      mid = (lo + hi)/2;

      int x = ex0 + mid * dx[direction], y = ye0 + mid * dy[direction];
      if (examine(x, y)) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    smallestJumpToUnflattenedInDirection[direction] = lo;
  }

  m = (ye0 + smallestJumpToUnflattenedInDirection[0]) - (ye0 - smallestJumpToUnflattenedInDirection[2]) - 1;
  ex1 = (ex0 - smallestJumpToUnflattenedInDirection[3]) + 1;
  ye1 = (ye0 - smallestJumpToUnflattenedInDirection[2]) + 1;

  ex2 = ex1;
  ye2 = ye1;

  // Go lower-left while possible
  while (examine(ex2 - m, ye2 - m)) {
    ex2 -= m;
    ye2 -= m;
  }

  // Go left while possible
  while (examine(ex2 - 2 * m, ye2)) {
    ex2 -= 2 * m;
  }

  // Go down while possible
  while (examine(ex2, ye2 - 2 * m)) {
    ye2 -= 2 * m;
  }

  solution(ex2 + 2 * m + (m + 1)/2 - 1, ye2 + 2 * m + (m + 1)/2 - 1);
}

int main() {
  cin >> n >> ex0 >> ye0;
  solve();
}
