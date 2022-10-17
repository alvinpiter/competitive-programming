/*
Observations:
* Player takes ceil(n/2) computers, system takes floor(n/2) computers.
* Computers taken by either the player or the system form a subarray.
* After the player choose the first computer, the system can control which computers will end up for the player.
  The system can do so by "copying" player's move.

With the above observation, we will take the maximum of the minimum sum of values in a segment involving the i-th computer.
*/

#include<bits/stdc++.h>
using namespace std;

int main() {
  int n, a[1000003], psum[1000003], ans;

  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }

  psum[0] = a[0];
  for (int i = 1; i < 2 * n; i++) {
    psum[i] = psum[i - 1] + a[i];
  }

  int cntTakenByPlayer = n/2 + n%2;

  multiset<int> segmentSums;

  ans = 0;
  for (int i = 0; i + cntTakenByPlayer - 1 < 2 * n; i++) {
    segmentSums.insert(psum[i + cntTakenByPlayer - 1] - (i == 0 ? 0 : psum[i - 1]));
    if (i >= cntTakenByPlayer) {
      int sumEndingAtPreviousIdx = psum[i - 1] - (i - 1 - cntTakenByPlayer >= 0 ? psum[i - 1 - cntTakenByPlayer] : 0);
      segmentSums.erase(segmentSums.find(sumEndingAtPreviousIdx));
    }

    // This is important, so we don't take the wrong minimums.
    // The minimums of the segments involving the earlier values will be handled in the later iterations.
    if (i >= cntTakenByPlayer - 1) {
      ans = max(ans, *(segmentSums.begin()));
    }
  }

  cout << ans << endl;
}
