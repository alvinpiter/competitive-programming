/*
Observations:
* Since the weight of each item is >= 1, we can take at most 2000 items.
* The weight of each item is <= 2000. This allow us to group the items and only take the top 2000 most expensive ones.
  We can have tighter bound tho, for example, when considering items with weight x, we can take at most 2000/x items.

Dynamic programming solution:
dp[w][c] -> maximum price achievable if we only consider items whose weight is between 1..w and our
bag capacity is c.

The complexity of the solution is around W^2 log W.
The log factor comes from the second observation.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXW 2000

int S, N, dp[MAXW + 3][MAXW + 3];
vector<pair<int, int> > itemsWithWeight[MAXW + 3];
vector<int> itemPricesWithWeight[MAXW + 3];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> S >> N;
  for (int i = 1; i <= N; i++) {
    int v, w, k;
    cin >> v >> w >> k;

    itemsWithWeight[w].push_back({v, k});
  }

  for (int w = 1; w <= MAXW; w++) {
    sort(itemsWithWeight[w].rbegin(), itemsWithWeight[w].rend());
    for (auto [price, count]: itemsWithWeight[w]) {
      for (int i = 0; i < count && itemPricesWithWeight[w].size() * w <= MAXW; i++) {
        itemPricesWithWeight[w].push_back(price);
      }
    }
  }

  memset(dp, 0, sizeof(dp));
  for (int w = 1; w <= MAXW; w++) {
    for (int cap = 1; cap <= S; cap++) {
      // Skip all items with weight w.
      dp[w][cap] = dp[w - 1][cap];

      int sumPrice = 0;
      int sumWeight = 0;
      for (auto price: itemPricesWithWeight[w]) {
        sumPrice += price;
        sumWeight += w;

        if (sumWeight <= cap) {
          dp[w][cap] = max(dp[w][cap], sumPrice + dp[w - 1][cap - sumWeight]);
        } else {
          break;
        }
      }
    }
  }

  cout << dp[MAXW][S] << endl;
}
