/*
To maximize the average elevations of the left over squares, we must find an inside sub-rectangle
whose total elevations is minimal.

Precompute the following:
bestSubRect[column][row] = The row number of the best sub-rectangle among sub-rectangles whose top-left coordinates are
(row, column), (row + 1, column), ..., (row + ((b - 2) - d), column).

We can do so by using monotonic queue technique in O(n^2).

To find the best rectangle, we again use monotonic queue technique and use the bestSubRect values that we've
computed before. Total complexity is O(n^2).

Test case:
6 6 5 4 1 1
2 7 4 1 1 6
5 10 1 3 10 6
5 9 10 6 7 10
2 1 6 4 8 3
7 10 4 3 2 5
9 5 4 6 1 5

Output should be 114
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int m, n, a, b, c, d, prefixSum[MAXN + 3][MAXN + 3];
int bestSubRect[MAXN + 3][MAXN + 3];

int sum(int r1, int c1, int r2, int c2) {
  return prefixSum[r2][c2] - prefixSum[r2][c1 - 1] - prefixSum[r1 - 1][c2] + prefixSum[r1 - 1][c1 - 1];
}

void initializeBestSubRect() {
  int windowSize = (b - 2) - d + 1;
  for (int column = 1; column + c - 1 <= m; column++) {
    /*
    Stores (sum, row).
    The front will contain smallest sum (and smallest row).
    */
    deque<pair<int, int> > dq;

    int rowPtr = 1;
    for (int row = 1; row + (windowSize - 1) + d - 1 <= n; row++) {
      // Remove obsolete sub-rectangles
      while (!dq.empty() && dq.front().second < row) {
        dq.pop_front();
      }

      // Add the new ones
      while ((rowPtr - 1) - row + 1 < windowSize) {
        int currSum = sum(rowPtr, column, rowPtr + d - 1, column + c - 1);
        while (!dq.empty() && dq.back().first >= currSum) {
          dq.pop_back();
        }

        dq.push_back(make_pair(currSum, rowPtr));
        rowPtr += 1;
      }

      bestSubRect[column][row] = dq.front().second;
    }
  }
}

int main() {
  cin >> m >> n >> a >> b >> c >> d;

  memset(prefixSum, 0, sizeof(prefixSum));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> prefixSum[i][j];

      prefixSum[i][j] += prefixSum[i - 1][j];
      prefixSum[i][j] += prefixSum[i][j - 1];
      prefixSum[i][j] -= prefixSum[i - 1][j - 1];
    }
  }

  initializeBestSubRect();

  int bestSum = 0;
  pair<int, int> bestRect, bestSmallRect; // {column, row}
  for (int row = 1; row + b - 1 <= n; row++) {
    deque<pair<int, pair<int, int> > > dq; // {sum, {column, row}}

    int ptrColumn = 2;
    for (int column = 1; column + a - 1 <= m; column++) {
      // Remove obsolete sub-rectangles
      while (!dq.empty() && dq.front().second.first <= column) {
        dq.pop_front();
      }

      // Add the new ones
      while (true) {
        int subRectRightColumn = ptrColumn + c - 1;
        int rectRightColumn = column + a - 1;
        if (subRectRightColumn >= rectRightColumn) {
          break;
        }

        int currSubRectSum = sum(bestSubRect[ptrColumn][row + 1], ptrColumn, bestSubRect[ptrColumn][row + 1] + d - 1, ptrColumn + c - 1);
        while (!dq.empty() && dq.back().first >= currSubRectSum) {
          dq.pop_back();
        }

        dq.push_back(make_pair(currSubRectSum, make_pair(ptrColumn, bestSubRect[ptrColumn][row + 1])));
        ptrColumn += 1;
      }

      int bestSubRectCol = dq.front().second.first;
      int bestSubRectRow = dq.front().second.second;

      int currSum = sum(row, column, row + b - 1, column + a - 1);
      currSum -= sum(bestSubRectRow, bestSubRectCol, bestSubRectRow + d - 1, bestSubRectCol + c - 1);

      if (currSum > bestSum) {
        bestSum = currSum;
        bestRect = make_pair(column, row);
        bestSmallRect = make_pair(bestSubRectCol, bestSubRectRow);
      }
    }
  }

  cout << bestRect.first << " " << bestRect.second << endl;
  cout << bestSmallRect.first << " " << bestSmallRect.second << endl;
}
