/*
It is easier to count how many pairs of cows which are compatible with each other.

If a cow likes flavors f1, f2, f3, f4 and f5, then the cows which are compatible with them
are the cows which like f1 or f2 or f3 or f4 or f5. This can be calculated with inclusion-exclusion
principle.

The number of possible subsets of flavor is quite small, which is 31*n.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int

struct FiveInts {
  int sz;
  int ints[5]; // If sz < 5, the suffix of ints will be zeroes

  bool operator<(const FiveInts& other) const {
    for (int i = 0; i < 5; i++) {
      if (ints[i] < other.ints[i]) return true;
      if (ints[i] > other.ints[i]) return false;
    }
    return false;
  }
};

int n, f[5];
map<FiveInts, int> cntLikes;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  freopen("cowpatibility.in", "r", stdin);
  freopen("cowpatibility.out", "w", stdout);

  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 5; j++) {
      cin >> f[j];
    }

    sort(f, f + 5);

    for (int mask = 1; mask < 32; mask++) {
      FiveInts subset;

      subset.sz = 0;
      for (int j = 0; j < 5; j++) {
        if (mask & (1 << j)) {
          subset.ints[subset.sz++] = f[j];
        }
      }

      for (int idx = subset.sz; idx < 5; idx++) {
        subset.ints[idx] = 0;
      }

      cntLikes[subset] += 1;
    }
  }

  LL cntCompatible = 0;
  for (auto [subset, cnt]: cntLikes) {
    LL cntPair = ((LL) cnt * cnt - cnt)/2;
    if (subset.sz%2 == 1) {
      cntCompatible += cntPair;
    } else {
      cntCompatible -= cntPair;
    }
  }

  cout << ((LL) n * n - n)/2 - cntCompatible << endl;
}
