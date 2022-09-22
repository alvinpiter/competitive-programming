/*
Algo:
* Put the first dish onto the first stack.
* For each new dish:
  * Find the first stack such that the base is > current dish
  * There will be 2 cases:
    * The top of the stack is < current dish. We need to pop from previous stacks and current stack.
    * The top of the stack is > current dish. Put the dish on current stack.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int solve(vector<int> dishes) {
  vector<int> counterStacks[MAXN + 3];

  int counterStacksPtr = 0;
  int numCounterStacks = 1;
  counterStacks[0].push_back(dishes[0]);

  int lastPoppedDish = 0;
  int ans = 1;

  for (int i = 1; i < dishes.size(); i++) {
    if (dishes[i] < lastPoppedDish) {
      break;
    }

    int lo = counterStacksPtr, hi = counterStacksPtr + numCounterStacks - 1, mid;
    while (hi >= lo) {
      mid = (lo + hi)/2;
      if (counterStacks[mid][0] < dishes[i]) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    if (lo == counterStacksPtr + numCounterStacks) {
      numCounterStacks += 1;
      counterStacks[lo].push_back(dishes[i]);
    } else {
      if (dishes[i] < counterStacks[lo].back()) {
        counterStacks[lo].push_back(dishes[i]);
      } else {
        // Pop all previous stacks
        if (lo > 0) {
          lastPoppedDish = counterStacks[lo - 1][0];
        }

        // Pop some dishes from current stack
        while (dishes[i] > counterStacks[lo].back()) {
          lastPoppedDish = counterStacks[lo].back();
          counterStacks[lo].pop_back();
        }

        numCounterStacks -= (lo - counterStacksPtr);
        counterStacksPtr = lo;
      }
    }

    ans = i + 1;
  }

  return ans;
}

int main() {
  freopen("dishes.in", "r", stdin);
  freopen("dishes.out", "w", stdout);

  int n;
  vector<int> dishes;

  cin >> n;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;

    dishes.push_back(d);
  }

  cout << solve(dishes) << endl;
}
