/*
Assume we already know the number of rectangles on the first (i - 1) fence.

Define f(i) as (i * i + i)/2;

If we are to add the i-th fence, then the new rectangles can be categorized into 3:
* It lies completely on the i-th fence. There are f(h[i]) * f(w[i]) such rectangles.
* The right end ends on the i-th fence while the left end lies on taller fence to the left of it.
  We don't want to consider the taller fence that comes before a fence lower than the i-th fence.
  Let's say the first lower fence to the left of the i-th fence is the j-th fence.
  There are (sumWidth(j + 1, i) * w[i]) * f(h[i]) such rectangles.
* The right end ends on the i-th fence while the left end lies on lower fences.
  Assume we keep the lower fences on a stack:

  h_i1 < h_i2 < h_i3 ...
  We can create rectangles whose height is at most h_i3 using the (i2 + 1)-th fence upto the i3-th fence.
  There are (sumWidth(i2 + 1, i3) * w[i]) * f(h_i3) such rectangles.

  We can do the same calculation for the (i1 + 1)-th fence upto the i2-th fence, and so on.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 100000

int n;
LL h[MAXN + 3], w[MAXN + 3], sumWidth[MAXN + 3], sumFhw = 0, ans = 0;
stack<int> st;

LL f(LL k) {
  LL k1 = k + 1;
  return k%2 == 0 ? ((k/2)%MOD * (k1)%MOD)%MOD : (k%MOD * (k1/2)%MOD)%MOD;
}

int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }

  sumWidth[0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
    sumWidth[i] = sumWidth[i - 1] + w[i];
  }

  for (int i = 1; i <= n; i++) {
    LL rectanglesOnTheCurrentFence = (f(h[i]) * f(w[i]))%MOD;
    ans = (ans + rectanglesOnTheCurrentFence)%MOD;

    while (!st.empty() && h[st.top()] >= h[i]) {
      int top = st.top(); st.pop();

      LL totalWidth = sumWidth[top] - (st.empty() ? 0 : sumWidth[st.top()]);
      LL fhw = (f(h[top]) * (totalWidth%MOD))%MOD;
      sumFhw = (sumFhw - fhw + MOD)%MOD;
    }

    int firstLowerIdx = (st.empty() ? 0 : st.top());

    LL rectanglesOnTheCurrentFenceAndTallerNeighbors = (((sumWidth[i - 1] - sumWidth[firstLowerIdx])%MOD * w[i])%MOD * f(h[i]))%MOD;
    ans = (ans + rectanglesOnTheCurrentFenceAndTallerNeighbors)%MOD;

    LL rectanglesOnTheCurrentFenceAndLowerNeighbors = (sumFhw * w[i])%MOD;
    ans = (ans + rectanglesOnTheCurrentFenceAndLowerNeighbors)%MOD;

    LL totalWidth = sumWidth[i] - (st.empty() ? 0 : sumWidth[st.top()]);
    sumFhw = (sumFhw + (f(h[i]) * (totalWidth%MOD))%MOD)%MOD;

    st.push(i);
  }

  cout << ans << endl;
}
