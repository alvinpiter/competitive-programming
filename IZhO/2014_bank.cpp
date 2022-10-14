/*
dp[mask] -> The maximum number of prefix of salaries that we can pay using the banknotes represented by "mask".

Transition:
Brute force on the last used banknotes. Assume the last used banknote is the i-th:
* The number of paid salaries so far is k = dp[mask ^ (1 << i)]
* The next salary to pay is the (k + 1)-th one
* After paying the first k salaries, there might be leftover. Use this leftover together with the
  i-th banknote to pay for (k + 1)-th salary

Total complexity is O(m * 2^m)
*/

#include<bits/stdc++.h>
using namespace std;

int n, m, a[22], b[22], asum[22], bsum[(1 << 20) + 3];
int dp[(1 << 20) + 2];

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  asum[0] = a[0];
  for (int i = 1; i < n; i++) {
    asum[i] = asum[i - 1] + a[i];
  }

  for (int mask = 0; mask < (1 << m); mask++) {
    bsum[mask] = 0;
    for (int i = 0; i < m; i++) {
      if (mask & (1 << i)) {
        bsum[mask] += b[i];
      }
    }
  }

  dp[0] = 0;
  for (int mask = 1; mask < (1 << m); mask++) {
    dp[mask] = 0;

    for (int i = 0; i < m; i++) {
      if (mask & (1 << i)) {
        int prevMask = mask ^ (1 << i);

        // The current subset of bank notes must be at least as good
        // as the previous subset of bank notes.
        dp[mask] = max(dp[mask], dp[prevMask]);

        int leftOver = bsum[prevMask] - (dp[prevMask] > 0 ? asum[dp[prevMask] - 1] : 0);
        if (leftOver + b[i] == a[dp[prevMask]]) {
          dp[mask] = max(dp[mask], dp[prevMask] + 1);
          dp[mask] = min(dp[mask], n);
        }
      }
    }
  }

  cout << (dp[(1 << m) - 1] == n ? "YES" : "NO") << endl;
}
