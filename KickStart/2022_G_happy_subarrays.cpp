/*
If we have a subarray that starts at index X and ends at index Y, and it is not happy, then
all subarrays that starts at index X and ends at index Y' (Y' > Y) won't be happy either.
For each index X, we want to find the largest Y such that all subarrays (X..(X + 1)), (X..(X + 2)), ..., (X..Y) are happy.

Define prefixSum[j] as sigma(Ai), where 1 <= i <= j;

The prefix sum of a subarray that starts from index X is then: prefixSum[i] - prefixSum[X - 1]. If at some
point prefixSum[i] - prefixSum[X - 1] is negative, our subarray is not happy. To find such i, we can use monotonically
decreasing stack to find the "next smaller value".

Once we have the Y for each X, the problem becomes easy, we just need to evaluate the following sum:
A[X] * (Y - X + 1)
A[X + 1] * (Y - (X + 1) + 1)
A[X + 2] * (Y - (X + 2) + 1)
...
A[Y] * (Y - Y + 1)
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 400000
#define MAXLG 18

int t, n, prefixSum[MAXN + 3], nxt[MAXN + 3];
LL prefixSum2[MAXN + 3], ans;

int main() {
  cin >> t;
  for (int cases = 1; cases <= t; cases++) {
    cin >> n;

    prefixSum[0] = prefixSum2[0] = 0;
    for (int i = 1; i <= n; i++) {
      int a;
      cin >> a;
      prefixSum[i] = prefixSum[i - 1] + a;
      prefixSum2[i] = prefixSum2[i - 1] + (LL) a * i;
    }

    ans = 0;

    stack<int> st;
    for (int x = n; x >= 0; x--) {
      while (!st.empty() && prefixSum[x] <= prefixSum[st.top()]) {
        st.pop();
      }

      nxt[x] = (st.empty() ? n + 1 : st.top());
      st.push(x);
    }

    for (int x = n; x >= 1; x--) {
      int y = nxt[x - 1] - 1;

      LL currSum = (LL) (y + 1) * (prefixSum[y] - prefixSum[x - 1]) - (prefixSum2[y] - prefixSum2[x - 1]);
      ans += currSum;
    }

    cout << "Case #" << cases << ": " << ans << endl;
  }
}
