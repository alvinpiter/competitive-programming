/*
Observation 1:
There is a solution where we only operate on the prefix/suffix.

Proof of observation 1:
Assume we do "increase" operation on subarray L..R, where L > 1 and R < N.
We might as well increase the suffix (R + 1)..N and the result won't be worse.

Observation 2:
There is a solution where we only need to do "increase" operation.

Proof of observation 2:
"decrease" operation is only optimal when we do it on the prefix.
Instead of "decrease"-ing the prefix, we can "increase" the suffix and the result will be the same.

Observation 3:
We can always increase by x, i.e the maximum value.

The solution:
* Construct LIS[i] and LDS[i] (see code's comment).
* Assume we want to perform "increase" operation on suffix (i + 1). Then:
  - We need to find aj such that aj > ai - x.
  - Among all possible aj, pick the one with maximum LDS[j]. This can be done with segment tree.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, x, oriT[MAXN + 3], t[MAXN + 3];
int lis[MAXN + 3]; // lis[i] = The length of the longest increasing subsequence which ends at index i.
int lds[MAXN + 3]; // lds[i] = The length of the longest increasing subsequence which starts at index i.
vector<int> uniqTs;
int tree[8 * MAXN + 3];

void normalizeT() {
  sort(uniqTs.begin(), uniqTs.end());
  uniqTs.erase(unique(uniqTs.begin(), uniqTs.end()), uniqTs.end());

  for (int i = 1; i <= n; i++) {
    t[i] = (lower_bound(uniqTs.begin(), uniqTs.end(), t[i]) - uniqTs.begin()) + 1;
  }
}

void calculateLIS() {
  int best[MAXN + 3], currentLISLength = 0;
  for (int i = 1; i <= n; i++) {
    int pos = lower_bound(best + 1, best + currentLISLength + 1, t[i]) - best;
    if (pos == currentLISLength + 1) {
      currentLISLength += 1;
    }

    best[pos] = t[i];
    lis[i] = pos;
  }
}

void calculateLDS() {
  int best[MAXN + 3], currentLDSLength = 0;
  for (int i = n; i >= 1; i--) {
    int lo = 1, hi = currentLDSLength, mid;
    while (hi >= lo) {
      mid = (lo + hi)/2;
      if (best[mid] > t[i]) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    currentLDSLength = max(currentLDSLength, lo);

    best[lo] = t[i];
    lds[i] = lo;
  }
}

void updateTree(int nodeNum, int l, int r, int idx, int val) {
  if (r < idx || l > idx) {
    return;
  }

  if (l == r) {
    tree[nodeNum] = val;
    return;
  }

  int m = (l + r)/2;
  updateTree(2 * nodeNum, l, m, idx, val);
  updateTree(2 * nodeNum + 1, m + 1, r, idx, val);
  tree[nodeNum] = max(tree[2 * nodeNum], tree[2 * nodeNum + 1]);
}

int queryTree(int nodeNum, int l, int r, int ql, int qr) {
  if (r < ql || l > qr) {
    return 0;
  }

  if (l >= ql && r <= qr) {
    return tree[nodeNum];
  }

  int m = (l + r)/2;
  return max(
    queryTree(2 * nodeNum, l, m, ql, qr),
    queryTree(2 * nodeNum + 1, m + 1, r, ql, qr)
  );
}

int main() {
  cin >> n >> x;
  for (int i = 1; i <= n; i++) {
    cin >> oriT[i];

    t[i] = oriT[i];
    uniqTs.push_back(t[i]);
    uniqTs.push_back(t[i] - x);
  }

  normalizeT();
  calculateLIS();
  calculateLDS();

  memset(tree, 0, sizeof(tree));

  int ans = 0;
  for (int i = n; i >= 1; i--) {
    int minAj = (upper_bound(uniqTs.begin(), uniqTs.end(), oriT[i] - x) - uniqTs.begin()) + 1;
    int bestLds = queryTree(1, 1, 2*n, minAj, 2*n);

    ans = max(ans, lis[i] + bestLds);

    updateTree(1, 1, 2*n, t[i], lds[i]);
   }

   cout << ans << endl;
}
