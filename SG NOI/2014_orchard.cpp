/*
Solving the 1D case:
Assume the right end of our rectangle is at column c. Then we would like to find a column c', c' < c, such
that the number of zeroes in the rectangle plus the number of ones outside the rectangle is minimal.

Consider the following algorithm:

currentCost = bestCost = <num zeroes in the rectangle from column 1 to c>
for c' = 1 to c - 1:
  // Try excluding column c'.
  // If the value is 0, then our currentCost will decrease by 1.
  // If the value is 1, then our currentCost will increase by 1.

  delta = (c' == 0 ? -1 : 1)
  currentCost += delta
  bestCost = min(bestCost, currentCost)

We can see that the best c' for a c must be the prefix such that the sum of delta is minimum. This observation yields an
O(M) solution.

Solving the 2D case is similar, we just need to add an extra bruteforce for the top and bottom row of the rectangle, yielding
O(N^2 * M) solution.
*/

#include<bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

  int n, m;

  cin >> n >> m;

  int sum[n + 3][m + 3];
  memset(sum, 0, sizeof(sum));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      int num;
      cin >> num;

      sum[i][j] = num;
      sum[i][j] += sum[i - 1][j];
      sum[i][j] += sum[i][j - 1];
      sum[i][j] -= sum[i - 1][j - 1];
    }
  }

  int best = n * m;
  for (int r1 = 1; r1 <= n; r1++) {
    for (int r2 = r1; r2 <= n; r2++) {
      int numOnesAbove = sum[r1 - 1][m];
      int numOnesBelow = sum[n][m] - sum[r2][m];

      int deltaSum = 0;
      int bestDeltaSum = 0;
      for (int c = 1; c <= m; c++) {
        int numOnesToTheRight = c < m ? sum[r2][m] - sum[r1 - 1][m] - sum[r2][c] + sum[r1 - 1][c] : 0;

        int numOnesInCurrentColumn = sum[r2][c] - sum[r1 - 1][c] - sum[r2][c - 1] + sum[r1 - 1][c - 1];
        int numZeroesInCurrentColumn = (r2 - r1 + 1) - numOnesInCurrentColumn;
        int currentDelta = numOnesInCurrentColumn - numZeroesInCurrentColumn;

        // The cost if the rectangle spans from the first column up to the current column,
        // which is equal to the number of zeroes inside it
        int fullRectCost = (r2 - r1 + 1)*c - (sum[r2][c] - sum[r1 - 1][c]);
        int bestCostEndingHere = fullRectCost + bestDeltaSum;

        best = min(best, numOnesAbove + numOnesBelow + numOnesToTheRight + bestCostEndingHere);

        deltaSum += currentDelta;
        bestDeltaSum = min(bestDeltaSum, deltaSum);
      }
    }
  }

  cout << best << endl;
}
