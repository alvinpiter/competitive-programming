/*
dp[day][prev = 0/1] -> Maximum difference of number of roads traveled by Djowen and Djonatan starting from day "day" onwards if
previously Djowen is assigned to "prev". If prev = 0, Djowen was previously assigned to A[day - 1].

Calculating dp[day][0]:
Djowen picks A[day]:
(1) Difference of number of roads taken by Djowen and Djonatan: dist(A[day - 1], A[day]) - dist(B[day - 1], B[day])
(2) First option for Djonatan, assign Djowen to A[day + 1]: dist(A[day], A[day + 1]) - dist(B[day], B[day + 1]) + dp[day + 2][0]
(3) Second option for Djonatan, assign Djowen to B[day + 1]: dist(A[day], B[day + 1]) - dist(B[day], A[day + 1]) + dp[day + 2][1]

The result if Djowen picks A[day]: (1) + min((2), (3)). Min because Djonatan plays optimally too.

The other cases are derived in a similar way.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXLG 17
#define MAXN 200000
#define MAXM 200000

int N, M, A[MAXN + 3], B[MAXN + 3], dp[MAXN + 3][2];
int depth[MAXN + 3], P[MAXN + 3][MAXLG + 3];
bool isCalculated[MAXN + 3][2];
vector<int> adj[MAXN + 3];

void dfs(int u, int prev = -1) {
  for (auto v: adj[u]) {
    if (v != prev) {
      depth[v] = depth[u] + 1;
      P[v][0] = u;
      dfs(v, u);
    }
  }
}

int getLCA(int u, int v) {
  if (depth[u] > depth[v]) {
    swap(u, v);
  }

  int depthDiff = depth[v] - depth[u];
  for (int bit = 0; bit <= MAXLG; bit++) {
    if (depthDiff & (1 << bit)) {
      v = P[v][bit];
    }
  }

  if (u == v) {
    return u;
  }

  for (int bit = MAXLG; bit >= 0; bit--) {
    if (P[u][bit] != P[v][bit]) {
      u = P[u][bit];
      v = P[v][bit];
    }
  }

  return P[u][0];
}

int dist(int a, int b) {
  return depth[a] + depth[b] - 2 * depth[getLCA(a, b)];
}

int solve(int day, int prev) {
  if (day > M) {
    return 0;
  }

  if (isCalculated[day][prev]) {
    return dp[day][prev];
  }

  isCalculated[day][prev] = true;
  if (prev == 0) {
    int djowenToA = (dist(A[day - 1], A[day]) - dist(B[day - 1], B[day])) + min(
      dist(A[day], A[day + 1]) - dist(B[day], B[day + 1]) + solve(day + 2, 0),
      dist(A[day], B[day + 1]) - dist(B[day], A[day + 1]) + solve(day + 2, 1)
    );
    int djowenToB = (dist(A[day - 1], B[day]) - dist(B[day - 1], A[day])) + min(
      dist(B[day], A[day + 1]) - dist(A[day], B[day + 1]) + solve(day + 2, 0),
      dist(B[day], B[day + 1]) - dist(A[day], A[day + 1]) + solve(day + 2, 1)
    );

    return dp[day][prev] = max(djowenToA, djowenToB);
  } else {
    int djowenToA = (dist(B[day - 1], A[day]) - dist(A[day - 1], B[day])) + min(
      dist(A[day], A[day + 1]) - dist(B[day], B[day + 1]) + solve(day + 2, 0),
      dist(A[day], B[day + 1]) - dist(B[day], A[day + 1]) + solve(day + 2, 1)
    );
    int djowenToB = (dist(B[day - 1], B[day]) - dist(A[day - 1], A[day])) + min(
      dist(B[day], A[day + 1]) - dist(A[day], B[day + 1]) + solve(day + 2, 0),
      dist(B[day], B[day + 1]) - dist(A[day], A[day + 1]) + solve(day + 2, 1)
    );

    return dp[day][prev] = max(djowenToA, djowenToB);
  }
}

int main() {
  scanf("%d", &N);
  for (int i = 1; i < N; i++) {
    int u, v;
    scanf("%d%d", &u, &v);

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  memset(P, -1, sizeof(P));

  depth[1] = 0;
  dfs(1);

  for (int bit = 1; bit <= MAXLG; bit++) {
    for (int i = 1; i <= N; i++) {
      if (P[i][bit - 1] != -1) {
        P[i][bit] = P[P[i][bit - 1]][bit - 1];
      } else {
        P[i][bit] = -1;
      }
    }
  }

  scanf("%d", &M);
  A[0] = B[0] = 1;
  for (int i = 1; i <= M; i++) {
    scanf("%d%d", &A[i], &B[i]);
  }
  A[M + 1] = A[M];
  B[M + 1] = B[M];

  memset(isCalculated, false, sizeof(isCalculated));
  int res = solve(1, 0);

  if (res == 0) {
    printf("Draw 0\n");
  } else if (res < 0) {
    printf("Djonatan %d\n", -res);
  } else {
    printf("Djowen %d\n", res);
  }
}
