/*
sum-over-subset dynamic programming. Tutorial: https://codeforces.com/blog/entry/45223

dp1[mask][i]
How many mask' such that:
* mask | mask' = mask
* mask ^ mask' < 2^i ==> only the first i bit of mask' are allowed to differ with mask's

dp2[mask][i]
How many mask' such that:
* mask & mask' = mask
* mask ^ mask' < 2^i

dp3[mask][i]
How many mask' such that:
* The first i bit AND to 0
* mask ^ mask' < 2^i

For each number x, the answer to the problem will be:
dp1[x][MAXBIT], dp2[x][MAXBIT], n - dp3[x][MAXBIT]

The third number is due to us calculating the complement, i.e x AND y = 0.

Note: Need to use flying table technique to avoid MLE.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXBIT 21

int n, x[MAXN + 3], cnt[(1 << MAXBIT) + 3];
int dp1[(1 << MAXBIT) + 3][2];
int dp2[(1 << MAXBIT) + 3][2];
int dp3[(1 << MAXBIT) + 3][2];

int main() {
  cin >> n;

  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
    cnt[x[i]] += 1;
  }

  int t = 0;

  // base cases
  for (int mask = 0; mask < (1 << MAXBIT); mask++) {
    dp1[mask][t] = cnt[mask];
    dp2[mask][t] = cnt[mask];
    dp3[mask][t] = cnt[mask];
  }

  for (int bit = 1; bit <= MAXBIT; bit++) {
    t = 1 - t;
    for (int mask = 0; mask < (1 << MAXBIT); mask++) {
      bool isOn = (mask & (1 << (bit - 1))) > 0;
      if (isOn) {
        dp1[mask][t] = dp1[mask][1 - t] + dp1[mask ^ (1 << (bit - 1))][1 - t];
        dp2[mask][t] = dp2[mask][1 - t];
        dp3[mask][t] = dp3[mask ^ (1 << (bit - 1))][1 - t];
      } else {
        dp1[mask][t] = dp1[mask][1 - t];
        dp2[mask][t] = dp2[mask][1 - t] + dp2[mask ^ (1 << (bit - 1))][1 - t];
        dp3[mask][t] = dp3[mask][1 - t] + dp3[mask ^ (1 << (bit - 1))][1 - t];
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    cout << dp1[x[i]][t] << " " << dp2[x[i]][t] << " " << n - dp3[x[i]][t] << endl;
  }
}
