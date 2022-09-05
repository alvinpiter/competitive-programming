/*
Idea 1:
Assume we know the difference between an interval that starts from A[i] and an interval that starts from A[i + d].
Then it is easy to count the difference between an interval that starts from A[i + 1] and an interval that starts from
A[i + d + 1] because most of their elements are the same except the first and the last. We can do this quickly with
sliding window approach.

Idea 2:
We need to process the query in an offline manner. Assume we have a list of unique sorted queries.
If we are currently processing 2 intervals whose difference is k, then this result will affect the answer to
the queries whose value is >= k. We can do aggregate the result with something similar to prefix sum.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000
#define MAXQ 100

int n, l, a[MAXN + 3], q, mapToSortedUniqQuery[MAXN + 3];
int ans[MAXQ + 3][MAXN + 3];
vector<int> queries, sortedUniqQueries;

int main() {
  cin >> n >> l;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  cin >> q;
  for (int i = 0; i < q; i++) {
    int num;
    cin >> num;

    queries.push_back(num);
    sortedUniqQueries.push_back(num);
  }

  // Populate mapToSortedUniqQuery
  sort(sortedUniqQueries.begin(), sortedUniqQueries.end());
  sortedUniqQueries.erase(unique(sortedUniqQueries.begin(), sortedUniqQueries.end()), sortedUniqQueries.end());
  for (int k = 1; k <= n; k++) {
    mapToSortedUniqQuery[k] = lower_bound(sortedUniqQueries.begin(), sortedUniqQueries.end(), k) - sortedUniqQueries.begin() + 1;
  }

  memset(ans, 0, sizeof(ans));

  for (int d = 1; (1 + d) + (l - 1) <= n; d++) {
    int currentDiff = 0;
    for (int i = 1; i < l; i++) {
      currentDiff += (a[i] != a[i + d]);
    }

    int leftPtr = 1;
    for (int i = l; i + d <= n; i++) {
      currentDiff += (a[i] != a[i + d]);
      while (i - leftPtr + 1 > l) {
        currentDiff -= (a[leftPtr] != a[leftPtr + d]);
        leftPtr += 1;
      }

      ans[mapToSortedUniqQuery[currentDiff]][leftPtr] += 1;
      ans[mapToSortedUniqQuery[currentDiff]][leftPtr + d] += 1;
    }
  }

  // Apply the prefix sum
  for (int idx = 1; idx <= n - l + 1; idx++) {
    for (int qIndex = 1; qIndex <= sortedUniqQueries.size(); qIndex++) {
      ans[qIndex][idx] += ans[qIndex - 1][idx];
    }
  }

  for (int i = 0; i < q; i++) {
    int queryIndex = mapToSortedUniqQuery[queries[i]];
    for (int j = 1; j <= n - l + 1; j++) {
      if (j > 1) {
        cout << " ";
      }
      cout << ans[queryIndex][j];
    }
    cout << endl;
  }
}
