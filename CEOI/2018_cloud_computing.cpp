/*
Model the problem as a knapsack problem:
* Each computer will be treated as an item whose weight is numCores and the profit is -price
* Each order will be treated as an item whose weight is -numCores ans the profit is price
* To not worry about the clock rates, let's sort all computers and orders in decreasing order of clock rates.
  This guarantee each accepted order will be handled by computer with larger clock rates.

dp[i][numCores] -> Maximum profit if we only consider items i up to the last item and we currently have numCores.
*/

#include<bits/stdc++.h>
using namespace std;
#define LL long long int

struct Item {
  int deltaCores, clockRate, profit;
  Item(int deltaCores_, int clockRate_, int profit_): deltaCores(deltaCores_), clockRate(clockRate_), profit(profit_) {}
  bool operator<(Item other) const {
    if (clockRate != other.clockRate) {
      return clockRate > other.clockRate;
    } else {
      return deltaCores > other.deltaCores; // Make sure the available computer comes before the order
    }
  }
};

int main() {
  int n, m, totalCores = 0;
  LL dp[2][2000 * 50 + 3];
  vector<Item> items;

  cin >> n;
  for (int i = 0; i < n; i++) {
    int numCores, clockRate, price;
    cin >> numCores >> clockRate >> price;

    items.push_back(Item(numCores, clockRate, -price));
    totalCores += numCores;
  }

  cin >> m;
  for (int i = 0; i < m; i++) {
    int numCores, clockRate, price;
    cin >> numCores >> clockRate >> price;

    items.push_back(Item(-numCores, clockRate, price));
  }

  sort(items.begin(), items.end());

  int t = 0;
  memset(dp, 0, sizeof(dp));

  for (int i = n + m; i >= 1; i--) {
    t = 1 - t;
    for (int numCores = 0; numCores <= totalCores; numCores++) {
      dp[t][numCores] = dp[1 - t][numCores];
      if (numCores + items[i - 1].deltaCores >= 0) {
        dp[t][numCores] = max(dp[t][numCores], dp[1 - t][numCores + items[i - 1].deltaCores] + items[i - 1].profit);
      }
    }
  }

  cout << dp[t][0] << endl;
}
