/*
The idea:
* Model the fishing locations as a graph. From each fishing location, add an edge to the next closest fishing location. If there are multiple, then don't add
  any edge.
* The formed graph can have cycles with length at most 2.

For the first part, we can do so by doing the following dynamic programming:
topLeft[i][j] -> {minDist, locationId} the id of the closest fishing location, together with its distance. If there are multiple location, then the locationId is -1.

By doing the same thing for the other directions, i.e topRight, bottomLeft, bottomRight, we can solve the first part.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 2000
#define MAXK 300000

string dummy;
int N, M, K, Q, id[MAXN + 3][MAXN + 3], nxt[MAXK + 3], ans[MAXK + 3];
char grid[MAXN + 3][MAXN + 3];
vector<pair<int, int> > fishes;
pair<int, int> dp[MAXN + 3][MAXN + 3], tempDp[MAXN + 3][MAXN + 3];

pair<int, int> merge(pair<int, int> f, pair<int, int> s) {
  if (f.first != s.first) {
    return (f.first < s.first ? f : s);
  } else {
    if (f.second != s.second) {
      return {f.first, -1};
    } else {
      return f;
    }
  }
}

pair<int, int> increaseDistByOne(pair<int, int> pair) {
  return {pair.first + 1, pair.second};
}

int getEndPoint(int from) {
  if (nxt[from] == -1) {
    return from;
  }

  if (ans[from] != -1) {
    return ans[from];
  }

  if (nxt[nxt[from]] == from) {
    // cycle
    ans[nxt[from]] = from;
    return ans[from] = nxt[from];
  } else {
    return ans[from] = getEndPoint(nxt[from]);
  }
}

void resetTempDp() {
  for (int i = 0; i <= N + 1; i++) {
    for (int j = 0; j <= M + 1; j++) {
      tempDp[i][j] = {INF, -1};
    }
  }
}

int main() {
  cin >> dummy;
  cin >> N >> M >> K >> Q;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      cin >> grid[i][j];
      if (grid[i][j] == 'X') {
        id[i][j] = fishes.size();
        fishes.push_back({i, j});
      }
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      dp[i][j] = {INF, -1};
    }
  }

  // Top left
  resetTempDp();
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (grid[i][j] == 'X') {
        tempDp[i][j] = {0, id[i][j]};
      } else {
        tempDp[i][j] = increaseDistByOne(merge(tempDp[i - 1][j], tempDp[i][j - 1]));
      }

      dp[i][j] = merge(dp[i][j], tempDp[i - 1][j]);
    }
  }

  // Top right
  resetTempDp();
  for (int i = 1; i <= N; i++) {
    for (int j = M; j >= 1; j--) {
      if (grid[i][j] == 'X') {
        tempDp[i][j] = {0, id[i][j]};
      } else {
        tempDp[i][j] = increaseDistByOne(merge(tempDp[i - 1][j], tempDp[i][j + 1]));
      }

      dp[i][j] = merge(dp[i][j], tempDp[i][j + 1]);
    }
  }

  // Bottom left
  resetTempDp();
  for (int i = N; i >= 1; i--) {
    for (int j = 1; j <= M; j++) {
      if (grid[i][j] == 'X') {
        tempDp[i][j] = {0, id[i][j]};
      } else {
        tempDp[i][j] = increaseDistByOne(merge(tempDp[i + 1][j], tempDp[i][j - 1]));
      }

      dp[i][j] = merge(dp[i][j], tempDp[i][j - 1]);
    }
  }

  // Bottom right
  resetTempDp();
  for (int i = N; i >= 1; i--) {
    for (int j = M; j >= 1; j--) {
      if (grid[i][j] == 'X') {
        tempDp[i][j] = {0, id[i][j]};
      } else {
        tempDp[i][j] = increaseDistByOne(merge(tempDp[i + 1][j], tempDp[i][j + 1]));
      }

      dp[i][j] = merge(dp[i][j], tempDp[i + 1][j]);
    }
  }

  memset(nxt, -1, sizeof(nxt));
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (grid[i][j] == 'X' && dp[i][j].second != -1) {
        int u = id[i][j], v = dp[i][j].second;
        nxt[u] = v;
      }
    }
  }

  memset(ans, -1, sizeof(ans));
  for (int q = 1; q <= Q; q++) {
    int r, c;
    scanf("%d%d", &r, &c);

    int startingPoint = dp[r][c].second;
    if (startingPoint == -1) {
      printf("%d %d\n", r, c);
    } else {
      int endingPoint = getEndPoint(startingPoint);
      printf("%d %d\n", fishes[endingPoint].first, fishes[endingPoint].second);
    }
  }
}
