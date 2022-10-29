/*
Visualize the pasture as a 2D matrix, where each cell may contain a cow.
Each fence restrict our movement from one cell to one of its neighbor.

Since the coordinate of the fences and the cows are large, we need to "compress" it first.
After compression, there are at most 2N + C different row coordinate and 2N + C different
column coordinates. The pasture can then be stored in a 2D matrix of size (2N + C)*(2N + C).

After the matrix is built, this problem can easily be solved with DFS.

A little trick:
Translate each coordinate by 1. This is to handle the cases when the cow need to pass
through negative coordinates or coordinates > 1000000 to reach another cow. Example test case:
1 2
1 0 1 1000000
0 0
2 0
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 500
#define MAX_GRID 2000

int N, C;
int r1[MAXN + 3], c1[MAXN + 3], r2[MAXN + 3], c2[MAXN + 3], cowR[MAXN + 3], cowC[MAXN + 3];
vector<int> uniqR, uniqC;
bool canGo[MAX_GRID][MAX_GRID][4], hasCow[MAX_GRID][MAX_GRID], visited[MAX_GRID][MAX_GRID];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int getNormalizedR(int x) {
  return lower_bound(uniqR.begin(), uniqR.end(), x) - uniqR.begin();
}

int getNormalizedC(int y) {
  return lower_bound(uniqC.begin(), uniqC.end(), y) - uniqC.begin();
}

int dfs(int r, int c) {
  visited[r][c] = true;

  int result = (hasCow[r][c] ? 1 : 0);
  for (int direction = 0; direction < 4; direction++) {
    int nextR = r + dr[direction], nextC = c + dc[direction];
    if (nextR >= 0 && nextR <= uniqR.size() && nextC >= 0 && nextC <= uniqC.size() && !visited[nextR][nextC] && canGo[r][c][direction]) {
      result += dfs(nextR, nextC);
    }
  }

  return result;
}

int main() {
  freopen("crazy.in", "r", stdin);
  freopen("crazy.out", "w", stdout);

  cin >> N >> C;
  for (int i = 1; i <= N; i++) {
    cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
    r1[i] += 1; c1[i] += 1; r2[i] += 1; c2[i] += 1;

    uniqR.push_back(r1[i]);
    uniqR.push_back(r2[i]);
    uniqC.push_back(c1[i]);
    uniqC.push_back(c2[i]);
  }

  for (int i = 1; i <= C; i++) {
    cin >> cowR[i] >> cowC[i];
    cowR[i] += 1; cowC[i] += 1;

    uniqR.push_back(cowR[i]);
    uniqC.push_back(cowC[i]);
  }

  // Add imaginary vertical line (0, 0, 0, INF) and imaginary horizontal line (0, 0, INF, 0)
  uniqR.push_back(0);
  uniqR.push_back(INF);
  uniqC.push_back(0);
  uniqC.push_back(INF);

  sort(uniqR.begin(), uniqR.end());
  uniqR.erase(unique(uniqR.begin(), uniqR.end()), uniqR.end());

  sort(uniqC.begin(), uniqC.end());
  uniqC.erase(unique(uniqC.begin(), uniqC.end()), uniqC.end());

  memset(canGo, true, sizeof(canGo));
  for (int i = 1; i <= N; i++) {
    r1[i] = getNormalizedR(r1[i]);
    c1[i] = getNormalizedC(c1[i]);
    r2[i] = getNormalizedR(r2[i]);
    c2[i] = getNormalizedC(c2[i]);

    if (r1[i] == r2[i]) {
      // Horizontal line
      int from = min(c1[i], c2[i]) + 1;
      int to = max(c1[i], c2[i]);

      for (int j = from; j <= to; j++) {
        canGo[r1[i]][j][2] = false;
        canGo[r1[i] + 1][j][0] = false;
      }
    } else {
      // Vertical line
      int from = min(r1[i], r2[i]) + 1;
      int to = max(r1[i], r2[i]);

      for (int j = from; j <= to; j++) {
        canGo[j][c1[i]][1] = false;
        canGo[j][c1[i] + 1][3] = false;
      }
    }
  }

  memset(hasCow, false, sizeof(hasCow));
  for (int i = 1; i <= C; i++) {
    cowR[i] = getNormalizedR(cowR[i]);
    cowC[i] = getNormalizedC(cowC[i]);

    hasCow[cowR[i]][cowC[i]] = true;
  }

  memset(visited, false, sizeof(visited));

  int ans = 0;
  for (int i = 0; i <= uniqR.size(); i++) {
    for (int j = 0; j <= uniqC.size(); j++) {
      if (!visited[i][j]) {
        ans = max(ans, dfs(i, j));
      }
    }
  }

  cout << ans << endl;
}
