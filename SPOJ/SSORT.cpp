/*
Build the following graph:
Each position in the array is a vertex. If a vertex currently contains a number which
should not be there, then connect this vertex with the vertex where this number
should be at. The resulting graph will be a bunch of cycles.

If the cycle length is 1, then this number is on correct position.
If the cycle length is 2, then we swap the two numbers in this cycle.
If the cycle length is > 2, then we have 2 options:
* Use the minimal number in this array as the "pivot", i.e swap it with the number that
  should be at its position. Do this until every number is in position.
* Use the global minimal as the "pivot", hence we need an extra cost to swap the
  minimal number in the current cycle with the the global minimal.
*/

#include<bits/stdc++.h>
using namespace std;
#define INF 1000000
#define MAXN 1000

int main() {
  int n, tc = 0;

  while (true) {
    cin >> n;
    if (n == 0) {
      break;
    }

    vector<pair<int, int> > numberWithIndices;
    int globalMini = INF;
    for (int i = 0; i < n; i++) {
      int num;
      cin >> num;

      numberWithIndices.push_back({num, i});
      globalMini = min(globalMini, num);
    }

    sort(numberWithIndices.begin(), numberWithIndices.end());

    vector<bool> visited(n, false);

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        int cycleLength = 0, sum = 0, mini = INF;
        int current = i;
        while (!visited[current]) {
          visited[current] = true;

          cycleLength += 1;
          sum += numberWithIndices[current].first;
          mini = min(mini, numberWithIndices[current].first);

          current = numberWithIndices[current].second;
        }

        if (cycleLength == 1) {
          continue;
        } else if (cycleLength == 2) {
          ans += sum;
        } else {
          ans += min(
            mini * (cycleLength - 1) + (sum - mini),
            2 * (globalMini + mini) + globalMini * (cycleLength - 1) + (sum - mini)
          );
        }
      }
    }

    cout << "Case " << ++tc << ": " << ans << endl << endl;
  }
}
