/*
WLOG, the weight of the molecules are sorted in non-decreasing order.

Lemma:
If there is a subset of molecules with size k whose total weight is between l and u (inclusive),
then there is also a subarray of molecules with size k whose total weight is between l and u (inclusive).

Proof:
Let's see a prefix of size k. If the total weight is >= l, then we are done.

Otherwise, let's shift this prefix by 1 position to the right. The change in the total weight will be w[k + 1] - w[1]
(or w[b + 1] - w[a] if our subarray are currently from index a to b). By the constraint of the problem, this change
must be <= u - l. There are two cases to consider:
* The sum of the last suffix of size k is >= l and <= u. Then this is the subarray that we are looking for.
* The sum of the last suffix of size k is > u. Because the total weight changes by at most (u - l), at some point
during our shift we must have a total sum of >= l and <= u.

Note: the sum of the last suffix of size k can't be < l because it will contradict our first premise, i.e there is
a subset of molecules of size k whose total weight is between l and u.
*/

#include "molecules.h"
#include<bits/stdc++.h>
using namespace std;
#define LL long long int

std::vector<int> find_subset(int l, int u, std::vector<int> w) {
  vector<pair<int, int> > indexedWeights;
  for (int i = 0; i < w.size(); i++) {
    indexedWeights.push_back({w[i], i});
  }

  sort(indexedWeights.begin(), indexedWeights.end());

  vector<LL> prefixSum;
  prefixSum.push_back(indexedWeights[0].first);

  for (int i = 1; i < indexedWeights.size(); i++) {
    prefixSum.push_back(indexedWeights[i].first + prefixSum.back());
  }

  for (int i = 0; i < indexedWeights.size(); i++) {
    int lo = i, hi = indexedWeights.size() - 1, mid;
    while (hi >= lo) {
      mid = (lo + hi)/2;
      LL sum = prefixSum[mid] - (i == 0 ? 0 : prefixSum[i - 1]);

      if (sum < l) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    LL sum = prefixSum[lo] - (i == 0 ? 0 : prefixSum[i - 1]);
    if (sum >= l && sum <= u) {
      vector<int> result;
      for (int j = i; j <= lo; j++) {
        result.push_back(indexedWeights[j].second);
      }
      return result;
    }
  }

  vector<int> result;
  return result;
}
