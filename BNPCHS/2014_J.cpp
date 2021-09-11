#include<bits/stdc++.h>
using namespace std;
#define MAXN 20000

int main() {
  int tc;

  cin >> tc;
  for (int cases = 1; cases <= tc; cases++) {
    int n, sumX[MAXN + 3], maxY;

    cin >> n;

    vector<pair<int, int> > pos;

    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;

      pos.push_back(make_pair(x, y));
    }

    sort(pos.begin(), pos.end());

    sumX[0] = pos[0].first;
    maxY = pos[0].second;
    for (int i = 1; i < pos.size(); i++) {
      sumX[i] = sumX[i - 1] + pos[i].first;
      maxY = max(maxY, pos[i].second);
    }

    int mini = 1000000000;
    for (int i = 0; i < n; i++) {
      int costLeft = pos[i].first * (i + 1) - sumX[i];
      int costRight = (sumX[n - 1] - sumX[i]) - pos[i].first * (n - i - 1);

      mini = min(mini, costLeft + costRight + maxY);
    }

    cout << "Kasus #" << cases << ": " << mini << endl;
  }
}
