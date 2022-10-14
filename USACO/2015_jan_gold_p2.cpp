/*
dp[mask] -> maximum amount of time spent watching the movies (along with the minimum number of movies to achieve that) if
we consider only movies from the set represented by "mask".

Transition:
Bruteforce on the last watched movie, assume it is the i-th one.
* The amount of time spent watching the rest of the movies is represented by T = dp[mask ^ (1 << i)].
* Now we need to find a show time in the i-th movie that cross over T. If there is none, then we can't watch the i-th movie.
  If there is any, then update our dp.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 20
#define MAXC 1000

int N, L, D[MAXN + 3], C[MAXN + 3], S[MAXN + 3][MAXC + 3];
pair<int, int> dp[(1 << MAXN) + 3];

pair<int, int> getBestOption(pair<int, int> p1, pair<int, int> p2) {
  if (p1.first >= L && p2.first >= L) {
    return p1.second < p2.second ? p1 : p2;
  }

  if (p1.first != p2.first) {
    return p1.first < p2.first ? p2 : p1;
  } else {
    return p1.second < p2.second ? p1 : p2;
  }
}

int main() {
  freopen("movie.in", "r", stdin);
  freopen("movie.out", "w", stdout);

  cin >> N >> L;
  for (int i = 0; i < N; i++) {
    cin >> D[i] >> C[i];
    for (int j = 0; j < C[i]; j++) {
      cin >> S[i][j];
    }
  }

  dp[0] = make_pair(0, 0);
  for (int mask = 1; mask < (1 << N); mask++) {
    for (int i = 0; i < N; i++) {
      // Try watching the i-th movie last
      if (mask & (1 << i)) {
        int prevMask = mask ^ (1 << i);

        // The current set of movies is as good as the previous set of movies
        dp[mask] = getBestOption(dp[mask], dp[prevMask]);

        // Find the appropriate show time
        int showTimeIdx = (upper_bound(S[i], S[i] + C[i], dp[prevMask].first) - S[i]) - 1;
        if (showTimeIdx >= 0 && S[i][showTimeIdx] + D[i] > dp[prevMask].first) {
          dp[mask] = getBestOption(dp[mask], make_pair(S[i][showTimeIdx] + D[i], dp[prevMask].second + 1));
        }
      }
    }
  }

  auto ans = dp[(1 << N) - 1];
  if (ans.first < L) {
    cout << -1 << endl;
  } else {
    cout << ans.second << endl;
  }
}
