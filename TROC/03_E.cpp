/*
Observation: Only the blue piece can has Aij^K.
Proof: If the red piece has Aij^K, this means the blue piece reach (i, j) first. Which is impossible.

DP[turnNumber][redsRow][bluesRow] => the maximal point we can reach after "turnNumber" turns where the red piece
ends up at "redsRow"-th row and the blue piece ends up at "bluesRow"-th row. From these 3 parameters, we
can infer the column position of each piece.

The answer to the problem will be DP[2*(N - 1) + 2*(M - 1)][N][N].

Extra observations:
* redsRow and bluesRow can be made <= sqrt(10^5) <= 320. If the number of rows in the grid is larger than the number
  of columns, transpose the grid.
* Calculating the number of operations: turnNumber * N * N = (2*N + 2*M - 2)*N*N, where N*M = 10^5.
  The maximum value will be reached when N is about sqrt(10^5). Hence the number of operations is more or less 10^5 * sqrt(10^5)
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000

int main() {
  int N, M, K;

  cin >> N >> M >> K;

  vector<vector<int> > rawGrid, grid;
  for (int i = 0; i < N; i++) {
    vector<int> tempRow;
    for (int j = 0; j < M; j++) {
      int num;
      cin >> num;

      tempRow.push_back(num);
    }
    rawGrid.push_back(tempRow);
  }

  if (N > M) {
    for (int j = 0; j < M; j++) {
      vector<int> tempRow;
      for (int i = 0; i < N; i++) {
        tempRow.push_back(rawGrid[i][j]);
      }
      grid.push_back(tempRow);
    }

    swap(N, M);
  } else {
    for (int i = 0; i < N; i++) {
      vector<int> tempRow;
      for (int j = 0; j < M; j++) {
        tempRow.push_back(rawGrid[i][j]);
      }
      grid.push_back(tempRow);
    }
  }

  int dp[2][N + 3][N + 3];

  // Base case
  int t = 0;
  for (int r1 = 0; r1 < N; r1++) {
    for (int r2 = 0; r2 < N; r2++) {
      dp[t][r1][r2] = (r1 == 0 && r2 == 0 ? 0 : -INF);
    }
  }

  for (int turnNumber = 1; turnNumber <= 2*(N - 1) + 2*(M - 1); turnNumber++) {
    t = 1 - t;
    for (int r1 = 0; r1 < N; r1++) {
      for (int r2 = 0; r2 < N; r2++) {
        int numMovesByFirstPiece = (turnNumber + 1)/2;
        int numMovesBySecondPiece = turnNumber/2;

        int c1 = numMovesByFirstPiece - r1;
        int c2 = numMovesBySecondPiece - r2;

        // Handle out of bound
        if (c1 < 0 || c1 >= M || c2 < 0 || c2 >= M) {
          dp[t][r1][r2] = -INF;
          continue;
        }

        if (turnNumber%2 == 1) {
          // This move is made by first the first piece
          dp[t][r1][r2] = grid[r1][c1] + max((r1 > 0 ? dp[1 - t][r1 - 1][r2] : -INF), dp[1 - t][r1][r2]);
        } else {
          // This move is made by the second piece
          dp[t][r1][r2] = (grid[r2][c2] ^ (r2 == r1 && c2 == c1 ? K : 0)) + max((r2 > 0 ? dp[1 - t][r1][r2 - 1] : -INF), dp[1 - t][r1][r2]);
        }
      }
    }
  }

  cout << dp[t][N - 1][N - 1] << endl;
}
