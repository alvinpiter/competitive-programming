/*
Observation:
Define a "decreasing index" in a string as index i (i > 0), such that s[i] < s[i - 1].
A form-k string can have at most (k - 1) decreasing indices.

DP formula:
dp[n][k][c] -> The number of strings that agree with the suffix of the given string (starting from index n)
such that we can have at most k decreasing indices and the string starts with character c.

After calculating the above DP, we do the k-th lexicographically thing.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 50000
#define MAXK 10

int N, K;
LL R, dp[MAXN + 3][MAXK + 3][4];
string s;
char mapper[] = {'A', 'C', 'G', 'T'};

int main() {
  cin >> N >> K >> R;
  cin >> s;

  // base case
  for (int k = 0; k < K; k++) {
    for (int c = 0; c < 4; c++) {
      dp[N - 1][k][c] = (s[N - 1] == 'N' || s[N - 1] == mapper[c] ? 1 : 0);
    }
  }

  for (int n = N - 2; n >= 0; n--) {
    for (int k = 0; k < K; k++) {
      for (int c = 0; c < 4; c++) {
        if (s[n] != 'N' && s[n] != mapper[c]) {
          dp[n][k][c] = 0;
          continue;
        }

        for (int nextC = 0; nextC < 4; nextC++) {
          int cost = (nextC < c ? 1 : 0);
          if (cost <= k) {
            dp[n][k][c] += dp[n + 1][k - cost][nextC];
          }
        }
      }
    }
  }

  string ans = "";
  int kLeft = K - 1;
  LL rLeft = R;
  for (int i = 0; i < N; i++) {
    if (s[i] != 'N') {
      ans += s[i];
    } else {
      LL sumWays = 0;
      LL sumPrevWays = 0;
      for (int c = 0; c < 4; c++) {
        int cost = (i > 0 && mapper[c] < ans[i - 1] ? 1 : 0);
        sumWays += dp[i][kLeft - cost][c];

        if (sumWays >= rLeft) {
          ans += mapper[c];
          rLeft -= sumPrevWays;
          break;
        } else {
          sumPrevWays += dp[i][kLeft - cost][c];
        }
      }
    }

    kLeft -= (i > 0 && ans[i] < ans[i - 1] ? 1 : 0);
  }

  cout << ans << endl;
}
