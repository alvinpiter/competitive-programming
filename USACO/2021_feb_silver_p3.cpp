/*
Assume we can calculate the following:
F(m) -> The number of rectangular sub-grid such that the green-ness is at least m.

The answer to the problem is then F(100) - F(101).

To calculate F(m), we can do the following:
* Convert the green-ness matrix into a binary matrix, M[i][j] = 1 if G[i][j] >= m, 0 otherwise.
* Find the number of rectangular sub-grid in M that contains all 1.

The second point above can be done this way:
* Let's say we'd like to find all valid rectangles whose left-end column is at col1 and right-end column is
at col2.
* Call a row a "good" if the sum of M on the current row from column col1 to column col2 equals col2 - col1 + 1, or in other words,
this row contains all 1 from column col1 to column c2.
* The number of valid rectangles ending at a particular row equals to the number of consecutive "good" rows so far.

This yields an O(N^3) solution.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int n, g[503][503];

LL f(int mini) {
  int rowSum[503][503];
  memset(rowSum, 0, sizeof(rowSum));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      rowSum[i][j] = (g[i][j] >= mini ? 1 : 0);
      rowSum[i][j] += rowSum[i][j - 1];
    }
  }

  LL result = 0;
  for (int col1 = 1; col1 <= n; col1++) {
    for (int col2 = col1; col2 <= n; col2++) {
      int numGoodRowsSoFar = 0;
      for (int i = 1; i <= n; i++) {
        bool isRowGood = (rowSum[i][col2] - rowSum[i][col1 - 1] == col2 - col1 + 1);
        if (isRowGood) {
          result += (numGoodRowsSoFar + 1);
          numGoodRowsSoFar += 1;
        } else {
          numGoodRowsSoFar = 0;
        }
      }
    }
  }

  return result;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> g[i][j];
    }
  }

  cout << f(100) - f(101) << endl;
}
