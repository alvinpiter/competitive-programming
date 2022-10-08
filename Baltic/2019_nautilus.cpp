/*
dp[r][c][idx] -> Is it possible to reach cell (r, c) after executing idx-th command. idx starts from 1.

Base case:
dp[r][c][0] = 1 if isWater(r, c), 0 otherwise.

Transition:
command[idx] = 'N' -> dp[r][c][idx] = dp[r + 1][c][idx - 1] && isWater(r, c)
command[idx] = 'E' -> dp[r][c][idx] = dp[r][c - 1][idx - 1] && isWater(r, c)
command[idx] = 'S' -> dp[r][c][idx] = dp[r - 1][c][idx - 1] && isWater(r, c)
command[idx] = 'W' -> dp[r][c][idx] = dp[r][c + 1][idx - 1] && isWater(r, c)
command[idx] = '?' -> dp[r][c][idx] = (d[r + 1][c][idx - 1] & isWater(r, c)) | ...

Naive implementation will get TLE/MLE, because there are R*C*M states. We need C++'s bitset.

isWater(r) -> a bitset that represents whether a certain column in row r is filled with water.
dp[r][idx] -> a bitset that represents whether a certain column in row r can be reached after executing idx-th command.

command[idx] = 'N' -> dp[r][idx] = dp[r + 1][idx - 1] && isWater(r)
command[idx] = 'E' -> dp[r][idx] = (dp[r][idx - 1]) << 1) && isWater(r)
command[idx] = 'S' -> dp[r][idx] = dp[r - 1][idx - 1] && isWater(r)
command[idx] = 'W' -> dp[r][idx] = (dp[r][idx - 1] >> 1) && isWater(r)
command[idx] = '?' -> dp[r][idx] = (dp[r + 1][idx - 1] && isWater(r)) | ...

Notice the direction of the left shift and right shift. It is reversed because the bitset is indexed starting from 0
from the right.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXR 500
#define MAXM 5000

int R, C, M;
string command;
bitset<MAXR + 3> isWater[MAXR + 3], dp[MAXR + 3][MAXM + 3];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> R >> C >> M;

  for (int r = 1; r <= R; r++) {
    for (int c = 1; c <= C; c++) {
      char cell;
      cin >> cell;

      if (cell == '.') {
        isWater[r].set(c, 1);
        dp[r][0].set(c, 1);
      }
    }
  }

  cin >> command;

  for (int idx = 1; idx <= M; idx++) {
    for (int r = 1; r <= R; r++) {
      switch (command[idx - 1]) {
        case 'N':
          dp[r][idx] = dp[r + 1][idx - 1] & isWater[r];
          break;
        case 'E':
          dp[r][idx] = (dp[r][idx - 1] << 1) & isWater[r];
          break;
        case 'S':
          dp[r][idx] = dp[r - 1][idx - 1] & isWater[r];
          break;
        case 'W':
          dp[r][idx] = (dp[r][idx - 1] >> 1) & isWater[r];
          break;
        case '?':
          dp[r][idx] = (dp[r + 1][idx - 1] | (dp[r][idx - 1] << 1) | dp[r - 1][idx - 1] | (dp[r][idx - 1] >> 1)) & isWater[r];
          break;
      }
    }
  }

  int ans = 0;
  for (int r = 1; r <= R; r++) {
    for (int c = 1; c <= C; c++) {
      if (dp[r][M].test(c)) {
        ans += 1;
      }
    }
  }

  cout << ans << endl;
}
