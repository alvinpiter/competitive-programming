/*
If it is possible to reach the ratio at least r, then it is possible to reach the ratio at least r' (r' < r).
This is a hint for binary search solution.

Let's check whether it is possible to reach the ratio at least r.

The following conditions must hold:
sigma(Ti)/sigma(Wi) >= r
sigma(Ti) - r * sigma(Wi) >= 0
sigma(Ti - r * Wi) >= 0

and sigma(Wi) >= W.

For a specific r, we can model the problem as a knapsack problem.
Each item has weight Wi and value Ti - r * Wi. We'd like to find the
maximal value such that the total weight is at least W.

Implementation gotchas:
* r is not an integer, which will be harder to deal with. Luckily we are asked to print floor(1000r).
  Hence we can change the value of each item in our knapsack model to 1000*Ti - r' * Wi, where r' is floor(1000r).
* The sum of the weights of the items in our knapsack model is very big, however the capacity W is small.
  We can model the dp as follow:
  dp[n][w], where w < W: The max value achieveable from the first n items where the total weight is exactly w.
  dp[n][w], where w = W: The max value achieveable from the first n items where the total weight is at least w.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1000000000000LL
#define MAXN 250
#define MAXW 1000

int N, W, w[MAXN + 3], t[MAXN + 3];

bool check(LL r) {
  LL dp[MAXN + 3][MAXW + 3];

  dp[0][0] = 0;
  for (int w = 1; w <= W; w++) {
    dp[0][w] = -INF;
  }

  for (int i = 1; i <= N; i++) {
    LL value = (1000LL) * t[i] - r * w[i];

    for (int cap = 0; cap < W; cap++) {
      dp[i][cap] = dp[i - 1][cap];
      if (cap >= w[i]) {
        dp[i][cap] = max(dp[i][cap], value + dp[i - 1][cap - w[i]]);
      }
    }

    // Calculating dp[i][W]
    dp[i][W] = dp[i - 1][W];
    for (int cap = 0; cap <= W; cap++) {
      if (cap + w[i] >= W) {
        dp[i][W] = max(dp[i][W], value + dp[i - 1][cap]);
      }
    }
  }

  return dp[N][W] >= 0;
}

int main() {
  freopen("talent.in", "r", stdin);
  freopen("talent.out", "w", stdout);

  cin >> N >> W;
  for (int i = 1; i <= N; i++) {
    cin >> w[i] >> t[i];
  }

  LL lo = 1, hi = INF, mid;
  while (hi >= lo) {
    mid = (lo + hi)/2;
    if (check(mid)) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }

  cout << hi << endl;
}
