/*
Wrong DP: dp[n][e] -> max number of points and max amount of leftover energy that can be achieved from
the first n missions by using at most e energy.

Edge case:
2 5
5 4 2
4 1 100

Max point should be 102, but got 100 instead.

Correct DP: dp[a][e] -> max number of points and max amount of leftover energy that can be achieved from
missions whose A value is <= a by using at most e energy.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int N, E;
bool isCalculated[MAXN + 3][MAXN + 3];
pair<int, int> dp[MAXN + 3][MAXN + 3];
vector<pair<int, int> > whoWithA[MAXN + 3];

pair<int, int> solve(int a, int e) {
  if (a == 0) {
    return {0, e};
  }

  if (isCalculated[a][e]) {
    return dp[a][e];
  }

  pair<int, int> skip = solve(a - 1, e);
  pair<int, int> take = {0, 0};
  if (e >= a) {
    for (auto [b, x]: whoWithA[a]) {
      auto result = solve(e - a + b, e - a + b);
      take = max(take, {x + result.first, result.second});
    }
  }

  isCalculated[a][e] = true;
  return dp[a][e] = max(skip, take);
}

int main() {
  cin >> N >> E;
  for (int i = 1; i <= N; i++) {
    int a, b, x;
    cin >> a >> b >> x;
    whoWithA[a].push_back({b, x});
  }

  memset(isCalculated, false, sizeof(isCalculated));
  cout << solve(E, E).first << " " << solve(E, E).second << endl;
}
