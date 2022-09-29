/*
dp[l][r] = Maximum weight of cows such that the pies they are eating are in range l..r.
Transition: assume the last eaten pie is at index i, then dp[l][r] = max(dp[l][i - 1] + dp[l + 1][r] + heaviest[l][r][i]).

heaviest[l][r][i] = The weight of the heaviest cow whose pie range is in l..r and they like i-th pie.
To calculate heaviest[l][r][i], we do a "spreading"-like operation. From state (l, r, i), we try to spread it
to (l - 1, r, i) and (l, r + 1, i).
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 300

int N, M, W[MAXN * MAXN + 3], L[MAXN * MAXN + 3], R[MAXN * MAXN + 3];
int dp[MAXN + 3][MAXN + 3], heaviest[MAXN + 3][MAXN + 3][MAXN + 3];

int main() {
  freopen("pieaters.in", "r", stdin);
  freopen("pieaters.out", "w", stdout);

  cin >> N >> M;
  for (int i = 1; i <= M; i++) {
    cin >> W[i] >> L[i] >> R[i];

    /*
    In total, this loop is just O(N^3).
    This is due to the fact that there is no cow that like the exact same set of pies.
    */
    for (int j = L[i]; j <= R[i]; j++) {
      heaviest[L[i]][R[i]][j] = max(heaviest[L[i]][R[i]][j], W[i]);
    }
  }

  for (int i = 1; i <= N; i++) {
    for (int l = i; l >= 1; l--) {
      for (int r = i; r <= N; r++) {
        if (l > 1) {
          heaviest[l - 1][r][i] = max(heaviest[l - 1][r][i], heaviest[l][r][i]);
        }

        if (r < N) {
          heaviest[l][r + 1][i] = max(heaviest[l][r + 1][i], heaviest[l][r][i]);
        }
      }
    }
  }

  memset(dp, 0, sizeof(dp));
  for (int width = 1; width <= N; width++) {
    for (int l = 1; l + width - 1 <= N; l++) {
      int r = l + width - 1;
      for (int i = l; i <= r; i++) {
        dp[l][r] = max(dp[l][r], dp[l][i - 1] + dp[i + 1][r] + heaviest[l][r][i]);
      }
    }
  }

  cout << dp[1][N] << endl;
}
